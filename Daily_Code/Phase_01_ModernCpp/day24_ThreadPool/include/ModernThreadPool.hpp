#pragma once

#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <memory>
#include <stdexcept>
#include <type_traits>
#include <utility>

// 假设你有自己的日志库，如果没有可以替换为 std::cout
#include "MyLogger.hpp" 

class ThreadPool {
public:
    // 构造函数：启动固定数量的 Worker 线程
    explicit ThreadPool(size_t threads) : m_stop(false) {
        for (size_t i = 0; i < threads; ++i) {
            // 使用 emplace_back 直接在 vector 内存放位置构造线程对象
            m_workers.emplace_back([this, i] {
                // 每个工作线程的死循环逻辑（打工人的日常）
                while (true) {
                    std::function<void()> task;

                    { // --- 临界区开始 ---
                        // 使用 unique_lock 管理互斥锁，配合条件变量的等待/唤醒机制
                        std::unique_lock<std::mutex> lock(this->m_queueMutex);

                        // 线程休眠，交出 CPU 控制权。
                        // 醒来的条件：1. 收到停止信号 m_stop  或者  2. 任务队列不为空
                        // Lambda 表达式用于防止操作系统的“虚假唤醒”(Spurious Wakeup)
                        this->m_cv.wait(lock, [this] {
                            return this->m_stop || !this->m_tasks.empty();
                        });

                        // 如果收到停止信号，且队列里的任务都处理完了，线程就可以安全下班了
                        if (this->m_stop && this->m_tasks.empty()) {
                            LOG_INFO("[ThreadPool] Worker ", i, " is exiting.");
                            return;
                        }

                        // 从队列头取出一个任务，使用 std::move 避免 std::function 的深拷贝
                        task = std::move(this->m_tasks.front());
                        this->m_tasks.pop();
                    } // --- 临界区结束，互斥锁自动释放 ---

                    // 真正执行任务。
                    // 核心注意：执行任务时【绝对不能】在锁的作用域内，否则多线程就退化成了串行执行！
                    task();
                }
            });
        }
        LOG_INFO("[ThreadPool] Started with ", threads, " workers.");
    }

    // 析构函数：优雅关闭 (Graceful Shutdown)
    ~ThreadPool() {
        {
            // 加锁修改标志位
            std::unique_lock<std::mutex> lock(m_queueMutex);
            m_stop = true;
        }
        
        // 敲响下班铃，唤醒所有还在 wait() 休眠的闲置线程，让它们看到 stop 标志并退出循环
        m_cv.notify_all();

        // 遍历所有线程，阻塞主线程，等待所有打工人把手上正在干的任务做完再销毁线程池
        for (std::thread& worker : m_workers) {
            if (worker.joinable()) {
                worker.join();
            }
        }
        LOG_INFO("[ThreadPool] All workers stopped.");
    }

    // 终极任务提交接口 (支持任意函数签名，支持异步获取返回值)
    // 语法糖说明：
    // 1. template<class F, class... Args>：接收任意类型的可调用对象和任意数量的参数
    // 2. auto 返回值推导结合 std::future，实现异步结果获取
    template<class F, class... Args>
    auto enqueue(F&& f, Args&&... args) 
        -> std::future<typename std::result_of<F(Args...)>::type> 
    {
        // 编译期推导任务函数的返回值类型 (C++17 中通常换成 std::invoke_result_t)
        using return_type = typename std::result_of<F(Args...)>::type;

        // 【核心重构：使用 std::make_shared 和 Lambda 解决不可拷贝对象的入队问题】
        // std::packaged_task 只能移动不能拷贝，而 std::function 要求元素必须可拷贝。
        // 用 shared_ptr 包裹 packaged_task，入队时只需拷贝智能指针。
        // 使用 C++14 的广义捕获 (f = std::forward...) 完美转发函数对象。
        auto task = std::make_shared< std::packaged_task<return_type()> >(
            [func = std::forward<F>(f), args...]() mutable -> return_type {
                return func(args...);
            }
        );

        // 拿到属于这个任务的“取餐小票”
        std::future<return_type> res = task->get_future();

        { // 加锁，将包装好的任务塞进队列
            std::unique_lock<std::mutex> lock(m_queueMutex);
            
            // 严谨起见：如果线程池已经处于关闭状态，严禁再提交新任务
            if (m_stop) {
                throw std::runtime_error("[ThreadPool] enqueue on stopped ThreadPool");
            }

            // 将 task 智能指针拷贝进 Lambda 的闭包中，统一擦除为 void() 类型塞进队列
            m_tasks.emplace([task]() { 
                (*task)(); // 调用 packaged_task，执行真正的业务逻辑并保存返回值
            });
        }

        // 叫醒一个正在休眠的线程起来干活
        m_cv.notify_one();

        // 返回小票给调用者
        return res;
    }

    // 禁用拷贝构造和赋值操作 (遵循 RAII 资源独占原则)
    ThreadPool(const ThreadPool&) = delete;
    ThreadPool& operator=(const ThreadPool&) = delete;

private:
    std::vector<std::thread> m_workers;              // 线程数组 (打工人花名册)
    std::queue<std::function<void()>> m_tasks;       // 任务队列 (待办事项看板)
    
    std::mutex m_queueMutex;                         // 保护队列的互斥锁
    std::condition_variable m_cv;                    // 负责线程休眠/唤醒的条件变量
    bool m_stop;                                     // 线程池的生命周期开关
};
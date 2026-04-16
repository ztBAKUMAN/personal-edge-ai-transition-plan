#pragma once
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include "MyLogger.hpp" 

class ThreadPool {
public:
    // 构造函数：启动固定数量的 Worker 线程
    explicit ThreadPool(size_t threads) : m_stop(false) 
    {
        for (size_t i = 0; i < threads; ++i) 
        {
            // emplace_back 内部直接构造线程对象
            m_workers.emplace_back([this, i] 
                {
                // 每个线程的死循环逻辑
                while (true) 
                {
                    std::function<void()> task;
                    
                    { // 临界区开始
                        std::unique_lock<std::mutex> lock(this->m_queueMutex);
                        
                        // 线程睡觉，直到有任务或者线程池要停止了
                        this->m_cv.wait(lock, [this] {
                            return this->m_stop || !this->m_tasks.empty();
                        });
                        
                        // 如果收到停止信号且队列空了，线程退出
                        if (this->m_stop && this->m_tasks.empty()) {
                            LOG_INFO("[ThreadPool] Worker ", i, " is exiting.");
                            return;
                        }
                        
                        // 从队列中取出一个任务 (利用移动语义)
                        task = std::move(this->m_tasks.front());
                        this->m_tasks.pop();
                    } // 临界区结束，释放锁
                    
                    // 执行任务 (注意：执行任务时绝对不能加锁，否则就变串行了！)
                    task();
                }
            });
        }
        LOG_INFO("[ThreadPool] Started with ", threads, " workers.");
    }

    // 析构函数：优雅关闭
    ~ThreadPool() 
    {
        {
            std::unique_lock<std::mutex> lock(m_queueMutex);
            m_stop = true;
        }
        // 唤醒所有正在睡觉的线程，让它们看到 stop 标志并退出
        m_cv.notify_all();
        
        for (std::thread& worker : m_workers) 
        {
            if (worker.joinable()) {
                worker.join(); // 等待所有打工人收拾包袱下班
            }
        }
        LOG_INFO("[ThreadPool] All workers stopped.");
    }

    // 提交任务到队列
    void enqueue(std::function<void()> task) 
    {
        {
            std::unique_lock<std::mutex> lock(m_queueMutex);
            // 严谨起见，如果线程池已经停止，不允许再提交新任务
            if (m_stop) 
            {
                LOG_ERROR("[ThreadPool] enqueue on stopped ThreadPool");
                return;
            }
            m_tasks.emplace(std::move(task));
        }
        // 叫醒一个睡觉的线程起来干活
        m_cv.notify_one(); 
    }

private:
    std::vector<std::thread> m_workers;              // 线程数组 (打工人队伍)
    std::queue<std::function<void()>> m_tasks;       // 任务队列 (待办事项)
    
    std::mutex m_queueMutex;                         // 保护队列的锁
    std::condition_variable m_cv;                    // 信号灯
    bool m_stop;                                     // 线程池关闭标志
};
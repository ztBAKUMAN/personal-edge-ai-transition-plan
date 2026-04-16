#include "MyThreadPool.hpp"
#include <chrono>

int main() {
    MyLogger::getInstance().open("threadpool_test.log");
    LOG_INFO("=== ThreadPool Test Start ===");

    {
        // 创建一个包含 4 个线程的线程池
        ThreadPool pool(4);

        // 丢给它 10 个耗时任务
        for (int i = 0; i < 10; ++i) {
            pool.enqueue([i] {
                LOG_INFO("Task ", i, " is being processed...");
                // 模拟耗时操作 (比如寻路计算)
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
                LOG_INFO("Task ", i, " is DONE.");
            });
        }

        LOG_INFO("All tasks enqueued to the pool. Main thread is doing other things...");
        
        // 主线程稍微等一下，观察多线程交替执行
        std::this_thread::sleep_for(std::chrono::seconds(2));
    } // 离开作用域，触发 pool 的析构函数，等待所有任务完成并安全关闭

    LOG_INFO("=== ThreadPool Test End ===");
    return 0;
}
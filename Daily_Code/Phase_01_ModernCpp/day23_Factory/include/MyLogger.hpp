#pragma once
#include <iostream>
#include <string>
#include <mutex>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <queue>
#include <thread>
#include <condition_variable>

// 日志等级
enum class LogLevel
{
    EM_DEBUG,
    EM_INFO,
    EM_WARN,
    EM_ERROR
};

const std::string defaulFile = "server.log";

class MyLogger
{
public:
    // 获取单例
    static MyLogger &getInstance()
    {
        static MyLogger logger;
        return logger;
    };

    ~MyLogger()
    {
        {
            std::lock_guard<std::mutex> lock(m_queueMutex);
            m_exit = true;
        }
        m_cv.notify_all();
        if(m_workerThread.joinable())
        {
            m_workerThread.join();
        }
        // 析构时关闭文件
        if(m_logFile.is_open())
        {
            // 刷新缓冲, 确保最后日志写入
            m_logFile.flush();
            m_logFile.close();
        }
    }

    // 打开文件
    void open(const std::string& filename)
    {
        std::lock_guard<std::mutex> locker(m_mutex);
        if(m_logFile.is_open())
        {
            m_logFile.close();
        }
        // 以追加模式打开
        m_logFile.open(filename, std::ios::out | std::ios::app);
        if(!m_logFile.is_open())
        {
            std::cerr << "Failed to open logFile: " << filename << std::endl;
        }
    }

    // **变参模板函数：支持任意数量任意类型
    template <typename... Args>
    void Log(LogLevel level, const char *filename, int line, Args... args)
    {
        std::stringstream ss;
        // 当前时间
        auto nowTime = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        ss << "[" << std::put_time(std::localtime(&nowTime), "%H:%M:%S") << "]";

        // 日志等级
        const char* levelString = "";
        switch (level)
        {
        case LogLevel::EM_DEBUG:
            levelString = "[DEBUG]";
            break; // 蓝色
        case LogLevel::EM_INFO:
            levelString = "[INFO]";
            break; // 绿色
        case LogLevel::EM_WARN:
            levelString = "[WARN]";
            break; // 黄色
        case LogLevel::EM_ERROR:
            levelString = "[ERROR]";
            break; // 红色
        default:
            break;
        }
        // 等级信息
        ss << levelString << " ";
        // 实际内容
        ((ss << args << " "), ...);
        // 文件和行号
        ss << " (" << filename << ":" << line << ")" << std::endl;

        // 控制台输出
        std::cout << ss.str() << std::endl;

        // 加入队列
        {
            std::lock_guard<std::mutex> lock(m_queueMutex);
            m_tasks.push(ss.str());
        }
        // 唤醒线程
        m_cv.notify_one();
    }

private:
    MyLogger() : m_exit(false)
    {
        if(m_filename.empty())
        {
            m_filename = defaulFile;
        }
        open(m_filename);
        m_workerThread = std::thread(&MyLogger::processTask, this);
    }
    MyLogger(std::string fileName) : m_filename(fileName), m_exit(false)
    {
        open(m_filename);
        m_workerThread = std::thread(&MyLogger::processTask, this);
    }
    MyLogger(const MyLogger &obj) = delete;
    MyLogger &operator=(const MyLogger &obj) = delete;

    void processTask()
    {
        // 后台线程写入日志
        while(true)
        {
            std::string logMsg;
            // 获取任务
            {
                std::unique_lock<std::mutex> lock(m_queueMutex);
                // 等待队列不为空或退出
                m_cv.wait(lock, [this]{
                    return !m_tasks.empty() || m_exit;
                });

                if(m_exit && m_tasks.empty())
                {
                    break;
                }

                // 取出任务
                logMsg = std::move(m_tasks.front());
                m_tasks.pop();
            }
            // 写日志
            if(m_logFile.is_open())
            {
                m_logFile << logMsg << std::endl;
            }
        }
    }

private:
    std::mutex m_mutex;         // 保护logFile
    std::string m_filename;     // 文件名
    std::ofstream m_logFile;    // 日志文件
    // 异步成员
    std::mutex m_queueMutex;    // 保护日志队列
    std::condition_variable m_cv;   // 条件变量(信号灯)
    std::queue<std::string> m_tasks;// 日志队列
    std::thread m_workerThread; // 写日志线程
    bool m_exit;                // 是否退出
};

// 预处理将 __FILE__ 和 __LINE__ 自动替换为文件名和行号
// 使用宏替换避免调用时手动输入固定参数信息
#define LOG_DEBUG(...) MyLogger::getInstance().Log(LogLevel::EM_DEBUG, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_INFO(...) MyLogger::getInstance().Log(LogLevel::EM_INFO, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_WARN(...) MyLogger::getInstance().Log(LogLevel::EM_WARN, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_ERROR(...) MyLogger::getInstance().Log(LogLevel::EM_ERROR, __FILE__, __LINE__, __VA_ARGS__)
#ifndef __LOGGER__H__
#define __LOGGER__H__

#include <stdio.h>

#include <atomic>
#include <mutex>
#include <thread>

#include "Singleton.h"

#define Log(message, ...) Logger::Instance()._Log(message, ##__VA_ARGS__)
#define LogWarning(message, ...) Logger::Instance()._LogWarning(message, ##__VA_ARGS__)
#define LogError(message, ...) Logger::Instance()._LogError(message, ##__VA_ARGS__)

class Logger : public Singleton<Logger> {
public:
    Logger() = default;

    void Shutdown();
    void Initialize(const char* filename);

    void _Log(const char* message, ...);
    void _LogWarning(const char* message, ...);
    void _LogError(const char* message, ...);
    void Flush();
private:
    void _Log(const char* message, va_list args);
    void LoggingThread();
    void SetShutdown();
    FILE* m_File;
    std::mutex m_Mutex;
    std::thread m_Thread;
    std::atomic<bool> m_Shutdown;
};

#endif  //!__LOGGER__H__

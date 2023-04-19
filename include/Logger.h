#ifndef __LOGGER__H__
#define __LOGGER__H__

#include <stdio.h>

#include <atomic>
#include <mutex>
#include <thread>

#include "Singleton.h"

class Logger : public Singleton<Logger> {
public:
    Logger() = default;

    void Shutdown();
    void Initialize(const char* filename);

    void Log(const char* message, ...);
    void LogWarning(const char* message, ...);
    void LogError(const char* message, ...);
    void Flush();
private:
    void Log(const char* message, va_list args);
    void LoggingThread();
    FILE* m_File;
    std::mutex m_Mutex;
    std::thread m_Thread;
    std::atomic<bool> m_Shutdown;
};

#endif  //!__LOGGER__H__

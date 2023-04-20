#ifndef __LOGGER__H__
#define __LOGGER__H__

#include <stdio.h>

#include <atomic>
#include <mutex>
#include <thread>

#include "Singleton.h"

#define STRINGIFY_IMPL(x) #x
#define STRINGIFY(x) STRINGIFY_IMPL(x)

constexpr char* GetFileName(const char* path) {
	const char* filename = path;
	for (const char* p = path; *p; ++p) {
		if (*p == '/' || *p == '\\') {
			filename = p + 1;
		}
	}
	return (char*)filename;
}
#define GET_FILE_NAME(x, y) GetFileName(__FILE__ x y)

#define FILENAME GET_FILE_NAME(":", STRINGIFY(__LINE__))

#define Message(message, ...) Logger::Instance()._Output(message, ##__VA_ARGS__)
#define Log(message, ...) Logger::Instance()._Log(FILENAME, message, ##__VA_ARGS__)
#define LogWarning(message, ...) Logger::Instance()._LogWarning(FILENAME, message, ##__VA_ARGS__)
#define LogError(message, ...) Logger::Instance()._LogError(FILENAME, message, ##__VA_ARGS__)

class Logger : public Singleton<Logger> {
public:
    Logger() = default;

    void Shutdown();
    void Initialize(const char* filename);

	void _Output(const char* message, ...);
    void _Log(const char* fileName, const char* message, ...);
    void _LogWarning(const char* fileName, const char* message, ...);
    void _LogError(const char* fileName, const char* message, ...);
    void Flush();
private:
    void _Log(const char* fileName, const char* message, bool logError, va_list args);
    void LoggingThread();
    void SetShutdown();
    FILE* m_File;
    std::mutex m_Mutex;
    std::thread m_Thread;
    std::atomic<bool> m_Shutdown;
};

#endif  //!__LOGGER__H__

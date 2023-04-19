#ifndef __LOGGER__H__
#define __LOGGER__H__

#include <stdio.h>

#include "Singleton.h"

class Logger : public Singleton<Logger> {
public:
    Logger() = default;

    void Shutdown();
    void Initialize(const char* filename);

    void Log(const char* message, ...) const;
    void LogWarning(const char* message, ...) const;
    void LogError(const char* message, ...) const;
    void Flush();
private:
    FILE* m_File;
};

#endif  //!__LOGGER__H__

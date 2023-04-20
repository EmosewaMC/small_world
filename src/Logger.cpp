#include "Logger.h"

#include <cstdarg>
#include <ctime>
#include <iostream>

using std::cout;
using std::endl;

#define StartVaList(message) va_list args; va_start(args, message);
#define EndVaList va_end(args);

void Logger::Initialize(const char* filename) {
    m_File = fopen(filename, "wt");
    if (!m_File) {
        printf("Cannot open file %s for writing\n", filename);
    }
    m_Thread = std::thread(&Logger::LoggingThread, this);
}

void Logger::LoggingThread() {
    while (!m_Shutdown) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        Flush();
    }
    Log("Logging thread is shutting down at time %i", time(NULL));
}

void Logger::Shutdown() {
    if (m_Shutdown) return;
    m_Shutdown = true;
    m_Thread.join();
    Log("Ending the game at time %i", time(NULL));
    Flush();
    if (m_File) {
        fclose(m_File);
    }
}

void Logger::_LogError(const char* message, ...) {
    StartVaList(message);
    cout << "\033[1;31mERROR: \033[0m";
    fputs("ERROR: ", m_File);
    Log(message, args);
    EndVaList;
}

void Logger::_LogWarning(const char* message, ...) {
    StartVaList(message);
    cout << "\033[1;33mWARNING: \033[0m";
    fputs("WARNING: ", m_File);
    Log(message, args);
    EndVaList;
}

void Logger::_Log(const char* message, ...) {
    StartVaList(message);
    Log(message, args);
    va_end(args);
}

void Logger::Flush() {
    if (m_File) {
        fflush(m_File);
    }
}

void Logger::_Log(const char* message, va_list args) {
    char buffer[2048];
    vsnprintf(buffer, 2048, message, args);
    m_Mutex.lock();
    cout << buffer << endl;
    fputs(buffer, m_File);
    fputs("\n", m_File);
    m_Mutex.unlock();
} 

void Logger::SetShutdown() {
    m_Mutex.lock();
    m_Shutdown = true;
    m_Mutex.unlock();
}

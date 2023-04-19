#include "Logger.h"

#include <cstdarg>
#include <ctime>
#include <iostream>

using std::cout;
using std::endl;

void Logger::Initialize(const char* filename) {
    m_File = fopen(filename, "wt");
    if (!m_File) {
        printf("Cannot open file %s for writing\n", filename);
    }
}

void Logger::Shutdown() {
    Log("Ending the game at time %i", time(NULL));
    Flush();
    if (m_File) {
        fclose(m_File);
    }
}

void Logger::LogError(const char* message, ...) const {
    char buffer[2048];
    va_list args;
    va_start(args, message);
    vsnprintf(buffer, 2048, message, args);
    cout << "\033[1;31mERROR: \033[0m" << buffer << endl;
    fputs("ERROR: ", m_File);
    fputs(buffer, m_File);
    fputs("\n", m_File);
    va_end(args);
}

void Logger::LogWarning(const char* message, ...) const {
    char buffer[2048];
    va_list args;
    va_start(args, message);
    vsnprintf(buffer, 2048, message, args);
    cout << "\033[1;33mWARNING: \033[0m" << buffer << endl;
    fputs("WARNING: ", m_File);
    fputs(buffer, m_File);
    fputs("\n", m_File);
    va_end(args);
}

void Logger::Log(const char* message, ...) const {
    char buffer[2048];
    va_list args;
    va_start(args, message);
    vsnprintf(buffer, 2048, message, args);
    cout << buffer << endl;
    fputs(buffer, m_File);
    fputs("\n", m_File);
    va_end(args);
}

void Logger::Flush() {
    if (m_File) {
        fflush(m_File);
    }
}

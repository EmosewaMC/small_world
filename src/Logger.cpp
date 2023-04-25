#include "Logger.h"

#include <cstdarg>
#include <ctime>
#include <iostream>

using std::cout;
using std::cerr;
using std::endl;

#define StartVaList(message) va_list args; va_start(args, message);
#define EndVaList va_end(args);

bool Logger::Initialize(const char* filename) {
	m_File = fopen(filename, "wt");
	if (!m_File) {
		printf("Cannot open file %s for writing\n", filename);
		return false;
	}
	m_Thread = std::thread(&Logger::LoggingThread, this);
	return true;
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
	if (!m_File) return;
	Log("Shutdown logger at time %i", time(NULL));
	Flush();
	fclose(m_File);
}

void Logger::_LogError(const char* fileName, const char* message, ...) {
	StartVaList(message);
	cerr << "\033[1;31mERROR: \033[0m";
	fputs("ERROR: ", m_File);
	_Log(fileName, message, true, args);
	EndVaList;
}

void Logger::_LogWarning(const char* fileName, const char* message, ...) {
	StartVaList(message);
	cout << "\033[1;33mWARNING: \033[0m";
	fputs("WARNING: ", m_File);
	_Log(fileName, message, false, args);
	EndVaList;
}

void Logger::_Log(const char* fileName, const char* message, ...) {
	StartVaList(message);
	_Log(fileName, message, false, args);
	va_end(args);
}

void Logger::Flush() {
	if (m_File) {
		fflush(m_File);
	}
}

void Logger::_Log(const char* fileName, const char* message, bool logError, va_list args) {
	char buffer[2048];
	vsnprintf(buffer, 2048, message, args);
	m_Mutex.lock();
	if (!logError) {
		fputs("[", stdout);
		fputs(fileName, stdout);
		fputs("] ", stdout);
		fputs(buffer, stdout);
		fputs("\n", stdout);
	}
	else {
		fputs("[", stderr);
		fputs(fileName, stderr);
		fputs("] ", stderr);
		fputs(buffer, stderr);
		fputs("\n", stderr);
	}
	fputs("[", m_File);
	fputs(fileName, m_File);
	fputs("] ", m_File);
	fputs(buffer, m_File);
	fputs("\n", m_File);
	m_Mutex.unlock();
}

void Logger::SetShutdown() {
	m_Mutex.lock();
	m_Shutdown = true;
	m_Mutex.unlock();
}

void Logger::_Output(const char* message, ...) {
	StartVaList(message);
	char buffer[2048];
	vsnprintf(buffer, 2048, message, args);
	fputs(buffer, stdout);
	fputs(buffer, m_File);
	fputs("\n", m_File);
	EndVaList;
}

#ifndef SADZA_CLIENT_SYSLOG_HPP
#define SADZA_CLIENT_SYSLOG_HPP

#include "Sys/SysAssert.hpp"
#include <cstdio>
#include <cstdarg>
#include <ctime>
#include <chrono>
#include <fstream>
#include <queue>
#include <condition_variable>
#include <thread>
#include <mutex>

class SysLog {
public:
    SysLog();

    ~SysLog();

    enum Severity {
        None = 0,
        Info = 1 << 0,
        Warning = 1 << 1,
        Error = 1 << 2,
        Debug = 1 << 3,
        Console = 1 << 4,
        ConsoleIn = 1 << 5
    };

    static void Print(const Severity &severity, const char *format, ...);

    static const int MAX_SYS_LOG_MSG_SIZE = 8192;

private:

    struct UnformattedMesage {
        UnformattedMesage(const Severity &severity)
                : m_severity(severity) {
            std::time_t t = std::time(nullptr);
            m_date = std::localtime(&t);
            m_micro = (std::chrono::duration_cast<std::chrono::milliseconds>(
                    std::chrono::system_clock::now().time_since_epoch()).count() & 0x3E8);
        }

        long long m_micro;
        char m_text[SysLog::MAX_SYS_LOG_MSG_SIZE];
        Severity m_severity;
        std::tm *m_date;
    };

    static const char *SeverityString(const Severity &severity);

    void processEntries();

    static std::fstream file;
    static char m_buffer[MAX_SYS_LOG_MSG_SIZE];
    static int m_severity;
    bool running;

    // Thead variables
    std::thread loggingThread;
    static std::condition_variable condVar;
    static std::mutex queueMutex;
    static std::queue<UnformattedMesage> messagesQueue;
};

#endif //SADZA_CLIENT_SYSLOG_HPP

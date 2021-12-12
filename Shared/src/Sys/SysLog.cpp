#include "Sys/SysLog.hpp"

#include <cstring>
#include <iostream>

SysLog::SysLog() : running(true) {
    loggingThread = std::thread{&SysLog::processEntries, this};
}

SysLog::~SysLog() {
    running = false;
    loggingThread.detach();
    file.close();
}

void SysLog::Print(const SysLog::Severity &severity, const char *format, ...) {

    va_list args;
    va_start (args, format);

    UnformattedMesage msg(severity);
    int done = vsprintf(msg.m_text, format, args);
    if (done > MAX_SYS_LOG_MSG_SIZE) { printf("Message excessed max length size! (size: %d, max: %d)\n", done, 1024); }

    queueMutex.lock();
    messagesQueue.push(msg);
    queueMutex.unlock();
    condVar.notify_all();

    va_end (args);
}

const char *SysLog::SeverityString(const SysLog::Severity &severity) {
    switch (severity) {
        case Severity::Info: {
            return "Info";
        }
        case Severity::Warning: {
            return "Warning";
        }
        case Severity::Error: {
            return "Error";
        }
        case Severity::Debug: {
            return "Debug";
        }
        case Severity::Console: {
            return "Console out";
        }
        case Severity::ConsoleIn: {
            return "Console in";
        }
        default:
            return nullptr;
    }
}

void SysLog::processEntries() {

    {
#ifdef _CLIENT_
        const char *dir = "Client";
#else
        const char *dir = "Server";
#endif

        char filepath[128];
        std::time_t t = std::time(nullptr);
        std::tm *now = std::localtime(&t);
        sprintf(filepath, "Logs/%s/%02d.%02d.%02d_%02d.%02d.%02d.txt\0",
                dir, now->tm_mday, now->tm_mon + 1, now->tm_year - 100,
                now->tm_hour, now->tm_min, now->tm_sec);
        printf("Log File: %s\n", filepath);
        file.open(filepath, std::ios::out);
        if (not file.is_open()) {
            throw std::runtime_error("Cannot open log file!");
        }
    }

    while (running) {
        std::unique_lock lock(queueMutex);
        condVar.wait(lock, [this] { return !messagesQueue.empty(); });
        UnformattedMesage &msg = messagesQueue.front();
        int done;

        // Add date and log level to message
        done = sprintf(m_buffer, "[%02d.%02d.%02d %02d:%02d:%02d.%04lld] [%s]: %s\n",
                       msg.m_date->tm_mday, msg.m_date->tm_mon + 1, msg.m_date->tm_year - 100,
                       msg.m_date->tm_hour, msg.m_date->tm_min, msg.m_date->tm_sec,
                       msg.m_micro, SeverityString(msg.m_severity), msg.m_text);
        messagesQueue.pop();

        if (done > MAX_SYS_LOG_MSG_SIZE) {
            printf("Post Message excessed max length size! (size: %d, max: %d)\n", done, 1024);
        }

        if (m_severity & msg.m_severity) { printf("%s", m_buffer); }
        file << m_buffer;
        file.flush();
    }
}

char SysLog::m_buffer[MAX_SYS_LOG_MSG_SIZE] = {0};
int SysLog::m_severity =
#ifdef DEBUG
        SysLog::Severity::Debug | SysLog::Severity::Error | SysLog::Severity::Info | SysLog::Severity::Warning |
        SysLog::Severity::Console;
//SysLog::Severity::None;
#else
SysLog::Severity::Error | SysLog::Severity::Info | SysLog::Severity::Warning | SysLog::Severity::Console;
#endif

std::fstream SysLog::file;
std::condition_variable SysLog::condVar;
std::mutex SysLog::queueMutex;
std::queue<SysLog::UnformattedMesage> SysLog::messagesQueue;
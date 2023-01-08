#include "Log.h"

#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <thread>

namespace ppm
{
    static int PrintfToBuffer(char *buffer, int size, char *format, ...)
    {
        va_list ap;
        va_start(ap, format);
        int ret = vsnprintf(buffer, 100, format, ap);
        va_end(ap);
        return ret;
    }

    TimeStamp::TimeStamp()
    {
        timestamp_ = std::chrono::duration_cast<std::chrono::microseconds>(
                         std::chrono::system_clock::now().time_since_epoch())
                         .count();
    }

    std::ostream &operator<<(std::ostream &os, const TimeStamp &timestamp)
    {
        std::time_t time_t = timestamp.timestamp_ / 1000000;
        auto gmtime = std::localtime(&time_t);
        char buffer[32];
        strftime(buffer, 32, "%Y-%m-%d %T.", gmtime);
        char microseconds[7];
        sprintf(microseconds, "%06" PRIu64, timestamp.timestamp_ % 1000000);
        os << '[' << buffer << microseconds << ']';
        return os;
    }

    const std::string TimeStamp::to_string() const
    {
        std::stringstream ss;
        std::time_t time_t = timestamp_ / 1000000;
        auto gmtime = std::localtime(&time_t);
        char buffer[32];
        strftime(buffer, 32, "%Y-%m-%d %T.", gmtime);
        char microseconds[7];
        sprintf(microseconds, "%06" PRIu64, timestamp_ % 1000000);
        ss << '[' << buffer << microseconds << ']';
        return ss.str();
    }

    // Note if in Log.h can error: free(): double free detected in tcache 2
    std::string LOG::buffer_ = "";
    std::mutex LOG::log_mutex_;

    LOG &LOG::GetInstance()
    {
        static std::unique_ptr<LOG> instance_ptr(new LOG());
        return *instance_ptr;
    }

    LOGLEVEL LOG::GetLogLevel()
    {
        return this->log_level_;
    }

    void LOG::SetLogLevel(LOGLEVEL level)
    {
        this->log_level_ = level;
    }

    LOGTARGET LOG::GetLogTarget()
    {
        return this->log_target_;
    }

    void LOG::SetLogTarget(LOGTARGET target)
    {
        this->log_target_ = target;
    }

    void LOG::LogToTarget(
        LOGLEVEL loglevel,
        const char *filename,
        const char *function,
        int linenumber,
        const char *format,
        ...)
    {
        LOG::GetInstance().SetLogLevel(loglevel);
        if (LOG::GetInstance().GetLogTarget() & LOG_TARGET_FILE)
        {
            // todo
        }
        TimeStamp timestamp;
        buffer_ += timestamp.to_string();
        char *logLevel;
        if (loglevel == LOG_LEVEL_DEBUG)
        {
            logLevel = (char *)"DEBUG";
        }
        else if (loglevel == LOG_LEVEL_INFO)
        {
            logLevel = (char *)"INFO";
        }
        else if (loglevel == LOG_LEVEL_WARN)
        {
            logLevel = (char *)"WARNING";
        }
        else if (loglevel == LOG_LEVEL_ERROR)
        {
            logLevel = (char *)"ERROR";
        }

        char locInfo[100];
        char *format2 = (char *)"[PID:%4d][TID:%4d][%s][%s][%s:%d]";
        PrintfToBuffer(locInfo, 100, format2,
                       getpid(),
                       std::this_thread::get_id(),
                       logLevel,
                       filename,
                       function,
                       linenumber);
        buffer_ += std::string(locInfo);

        char logInfo2[256];
        va_list ap;
        va_start(ap, format);
        vsnprintf(logInfo2, 256, format, ap);
        va_end(ap);
        buffer_ += std::string(logInfo2);
        buffer_ += std::string("\n");
        if (LOG::GetInstance().GetLogTarget() & LOG_TARGET_CONSOLE)
        {
            switch (loglevel)
            {
            case LOG_LEVEL_ERROR:
                printf("\033[1;31m%s\033[0m", buffer_.c_str());
                break;
            case LOG_LEVEL_WARN:
                printf("\033[1;33m%s\033[0m", buffer_.c_str());
                break;
            case LOG_LEVEL_DEBUG:
                printf("\033[1;34m%s\033[0m", buffer_.c_str());
                break;
            case LOG_LEVEL_INFO:
                printf("\033[1;32m%s\033[0m", buffer_.c_str());
                break;
            }
        }

        buffer_.clear();
    }
}
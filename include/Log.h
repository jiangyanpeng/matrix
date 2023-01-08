#ifndef __PPM_LOG_H__
#define __PPM_LOG_H__

#include <memory>
#include <mutex>
#include <chrono>
#include <sstream>
#include <fstream>
#include <cinttypes>

#define MAX_SIZE 2 * 1024 * 1024 // 2M

namespace ppm
{
    // timestamp
    class TimeStamp
    {
    public:
        TimeStamp();
        TimeStamp(uint64_t timestamp) : timestamp_(timestamp) {}

        friend std::ostream &operator<<(std::ostream &os, const TimeStamp &timestamp);
        const std::string to_string() const;

    private:
        uint64_t timestamp_;
    };

    // log
    enum LOGLEVEL
    {
        LOG_LEVEL_NONE  = 0x00,
        LOG_LEVEL_ERROR = 0x01,
        LOG_LEVEL_WARN  = 0x02,
        LOG_LEVEL_DEBUG = 0x03,
        LOG_LEVEL_INFO  = 0x04,
    };

    enum LOGTARGET
    {
        LOG_TARGET_NONE    = 0x00,
        LOG_TARGET_CONSOLE = 0x01,
        LOG_TARGET_FILE    = 0x10
    };
    class LOG
    {
    public:
        LOG(const LOG &) = delete;
        LOG(LOG &&) = delete;
        LOG &operator=(const LOG &) = delete;
        LOG &operator=(LOG &&) = delete;
        ~LOG() = default;

        static LOG &GetInstance();

        LOGLEVEL GetLogLevel();
        void SetLogLevel(LOGLEVEL loglevel);

        LOGTARGET GetLogTarget();
        void SetLogTarget(LOGTARGET logtarget);

        static void LogToTarget(
            LOGLEVEL loglevel,
            const char *fileName,
            const char *function,
            int lineNumber,
            const char *format,
            ...);

    private:
        LOG() : save_path_(""), log_level_(LOG_LEVEL_NONE), log_target_(LOG_TARGET_CONSOLE)
        {
        }

    private:
        std::string save_path_;

        static std::mutex log_mutex_;
        static std::string buffer_;

        LOGLEVEL log_level_;
        LOGTARGET log_target_;
    };
}

#define LOG_DEBUG(...)  ppm::LOG::LogToTarget(ppm::LOG_LEVEL_DEBUG, __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define LOG_INFO(...)   ppm::LOG::LogToTarget(ppm::LOG_LEVEL_INFO, __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define LOG_WARN(...)   ppm::LOG::LogToTarget(ppm::LOG_LEVEL_WARN, __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__)
#define LOG_ERROR(...)  ppm::LOG::LogToTarget(ppm::LOG_LEVEL_ERROR, __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__)

#define ENTER() LOG_INFO("Enter")
#define EXIT()  LOG_INFO("Exit")
#define FAIL()  LOG_ERROR("Fail")

#endif // __PPM_LOG_H__
#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <mutex>

enum class LogLevel
{ 
    Debug = 1, 
    Info = 2, 
    Warning = 3, 
    Error = 4,
    Fatal = 5,
};

class BaseLogger
{
    class LogStream;
public:
    BaseLogger() = default;
    virtual ~BaseLogger() = default;

    virtual LogStream operator()(LogLevel nLevel = LogLevel::Debug);

protected:
    const tm* getLocalTime();
    void endline(LogLevel nLevel, std::string&& oMessage);
    virtual void output(const tm *p_tm,
        const char *str_level,
        const char *str_message) = 0;
private:
    std::mutex log_mutex_;
    tm localTime_;
};

class BaseLogger::LogStream : public std::ostringstream
{
public:
    LogStream(BaseLogger& oLogger, LogLevel nLevel)
        : oLogger_(oLogger), enumLevel_(nLevel) {};
    LogStream(const LogStream& ls)
        : oLogger_(ls.oLogger_), enumLevel_(ls.enumLevel_) {};
    ~LogStream()
    {
        oLogger_.endline(enumLevel_, std::move(str()));
    }
private:
    BaseLogger& oLogger_;
    LogLevel enumLevel_;
};

class FileLogger 
    : public BaseLogger
{
public:
    FileLogger() noexcept;
    FileLogger(const FileLogger&) = delete;
    FileLogger(FileLogger&&) = delete;
    FileLogger(std::string file_name);
    bool InitLogPath(std::string file_path, std::string file_name);
    virtual ~FileLogger();
private:
    virtual void output(const tm *p_tm,
        const char *str_level,
        const char *str_message);
private:
    std::ofstream log_file_;
    std::string file_name;
    std::string file_path;
};

extern FileLogger logging;

#define LOGDEBUG logging(LogLevel::Debug)
#define LOGINFO logging(LogLevel::Info)
#define LOGWARNING logging(LogLevel::Warning)
#define LOGERROR logging(LogLevel::Error)
#define LOGFATAL logging(LogLevel::Fatal)
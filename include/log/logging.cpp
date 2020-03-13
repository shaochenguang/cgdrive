#include <cassert>
#include <chrono>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <map>
#include <regex>
#include <windows.h>
#include "logging.h"

#ifdef _WIN32
#define localtime_r(_Time, _Tm) localtime_s(_Tm, _Time)
#endif

static const std::map<LogLevel, const char *> LevelStr =
{
    { LogLevel::Debug, "Debug" },
    { LogLevel::Info, "Info" },
    { LogLevel::Warning, "Warning" },
    { LogLevel::Error, "Error" },
    { LogLevel::Fatal, "Fatal" },
};

std::ostream& operator<< (std::ostream& stream, const tm* tm)
{
    return stream << 1900 + tm->tm_year << '-'
        << std::setfill('0') << std::setw(2) << tm->tm_mon + 1 << '-'
        << std::setfill('0') << std::setw(2) << tm->tm_mday << ' '
        << std::setfill('0') << std::setw(2) << tm->tm_hour << ':'
        << std::setfill('0') << std::setw(2) << tm->tm_min << ':'
        << std::setfill('0') << std::setw(2) << tm->tm_sec;
}

BaseLogger::LogStream BaseLogger::operator()(LogLevel nLevel)
{
    return LogStream(*this, nLevel);
}

const tm* BaseLogger::getLocalTime()
{
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);
    localtime_r(&in_time_t, &localTime_);
    return &localTime_;
}

void BaseLogger::endline(LogLevel nLevel, std::string&& oMessage)
{
    std::lock_guard<std::mutex> locker(log_mutex_);
    output(getLocalTime(), LevelStr.find(nLevel)->second, oMessage.c_str());
}

FileLogger::FileLogger() noexcept
    : BaseLogger()
{

}

FileLogger::FileLogger(std::string file_name)
{
    InitLogPath("", file_name);
}

bool FileLogger::InitLogPath(std::string file_path, std::string file_name)
{
    std::string valid_filename(file_name.size(), '\0');
    std::regex express("/|:| |>|<|\"|\\*|\\?|\\|");
    regex_replace(valid_filename.begin(),
        file_name.begin(),
        file_name.end(),
        express,
        "_");
    std::string path = file_path + valid_filename;
    log_file_.open(path,
        std::fstream::out | std::fstream::app | std::fstream::ate);
    assert(!log_file_.fail());
    return true;
}

FileLogger::~FileLogger()
{
    log_file_.flush();
    log_file_.close();
}

void FileLogger::output(const tm *p_tm,
    const char *str_level,
    const char *str_message)
{
    log_file_ << '[' << p_tm << ']'
        << '[' << str_level << "]"
        << " " <<"Thread id:"<< std::this_thread::get_id() <<" "<< str_message << std::endl;
    log_file_.flush();
}
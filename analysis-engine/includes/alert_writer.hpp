#ifndef ALERT_WRITER_HPP
#define ALERT_WRITER_HPP

#include <string>
#include <ctime>

struct Alert
{
    time_t timestamp;
    std::string ip;
    std::string type;
    std::string severity;
    std::string message;
    size_t count;
    Alert(time_t Timestamp, const std::string& Ip, size_t Total);
};

struct alertWriter
{
    std::string filePath;
    alertWriter(const std::string& Path);
    bool writeAlert(const Alert& Alert);
};

Alert buildAlert(time_t Timestamp, const std::string& Ip, time_t Windowsize, size_t Total);

#endif
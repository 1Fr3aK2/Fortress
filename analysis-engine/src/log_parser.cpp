#include <event.hpp>
#include <log_parser.hpp>
#include <sstream>
#include <chrono>
#include <sstream>
#include <iomanip>
#include <ctime>

logParser::logParser(const std::string& path) : file(path.c_str())
{    
    if (!file.is_open())
    {
        std::cerr << "Error: error opening the file\n";
        return ;
    }
}

logParser::~logParser()
{
    if (file.is_open())
        file.close();
}


bool logParser::parse(const std::string &line, Event &e)
{
    std::string value;
    std::string user;
    std::string password;

    if (line.find("ip") != std::string::npos)
    {
        value = parseLine(line, "ip");
        if (value.empty())
            return false;
        e.srcIp = value;
    }
    if (line.find("timestamp") != std::string::npos)
    {
        value = parseLine(line, "timestamp");
        if (value.empty())
            return false;
        std::tm tm = {};
        if (strptime(value.c_str(), "%Y-%m-%dT%H:%M:%SZ", &tm) == NULL)
            return false;
        e.timestamp = timegm(&tm);
    }
    if (line.find("port") != std::string::npos)
    {
        value = parseLine(line, "port");
        if (value.empty())
            return false;
        int port;
        std::stringstream ss(value);
        ss >> port;
        e.port = port;
    }
    if (line.find("client_version") != std::string::npos)
    {
        value = parseLine(line, "client_version");
        if (value.empty())
            return false;
        e.clientVersion = value;
    }
    if (line.find("user") != std::string::npos)
    {
        value = parseLine(line, "user");
        if (value.empty())
            return false;
        e.user = value;
    }
    if (line.find("password") != std::string::npos)
    {
        value = parseLine(line, "password");
        if (value.empty())
            return false;
        e.password = value;
    }
    return true;
}

std::string logParser::parseLine(const std::string& line, const std::string &key)
{
    std::string value;
    size_t pos;
    size_t ddots = line.find(":");
    if (ddots == std::string::npos)
        return "";
    pos = line.find(key);
    if (pos != std::string::npos)
    {
        size_t start = ddots + 3;
        size_t end = line.find("\"", start);
        if (end == std::string::npos)
            return "";
        value = line.substr(start , end - start);
        if (value.empty())
            return "";
    }
    return value;
}

bool logParser::nextEvent(Event &event)
{
    std::string line;
    Event e;
    while (std::getline(file, line))
    {
        if (line.find("{") != std::string::npos)
            e = Event();
        else if (line.find("}") != std::string::npos)
        {
            event = e;
            return true;
        }
        else
            parse(line, e);
    }
    return false;    
}
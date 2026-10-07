#include <event.hpp>
#include <log_parser.hpp>
#include <sstream>
#include <ctime>
#include <iostream>

logParser::logParser(const std::string& Path) : file(Path.c_str())
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


bool logParser::parse(const std::string& Line, Event& Event)
{
    std::string Value;

    if (Line.find("\"ip\"") != std::string::npos)
    {
        Value = parseLine(Line, "ip");
        if (Value.empty())
            return false;
        Event.srcIp = Value;
    }
    if (Line.find("\"timestamp\"") != std::string::npos)
    {
        Value = parseLine(Line, "timestamp");
        if (Value.empty())
            return false;
        std::tm tm = {};
        if (strptime(Value.c_str(), "%Y-%m-%dT%H:%M:%SZ", &tm) == NULL)
            return false;
        Event.timestamp = timegm(&tm);
    }
    if (Line.find("\"port\"") != std::string::npos)
    {
        Value = parseLine(Line, "port");
        if (Value.empty())
            return false;
        int port;
        std::stringstream ss(Value);
        ss >> port;
        Event.port = port;
    }
    if (Line.find("\"client_version\"") != std::string::npos)
    {
        Value = parseLine(Line, "client_version");
        if (Value.empty())
            return false;
        Event.clientVersion = Value;
    }
    if (Line.find("\"user\"") != std::string::npos)
    {
        Value = parseLine(Line, "user");
        if (Value.empty())
            return false;
        Event.user = Value;
    }
    if (Line.find("\"password\"") != std::string::npos)
    {
        Value = parseLine(Line, "password");
        if (Value.empty())
            return false;
        Event.password = Value;
    }
    return true;
}

std::string logParser::parseLine(const std::string& Line, const std::string &Key)
{
    std::string Value;
    size_t Pos;
    size_t Ddots = Line.find(":");
    if (Ddots == std::string::npos)
        return "";
    Pos = Line.find(Key);
    if (Pos != std::string::npos)
    {
        size_t start = Ddots + 3;
        size_t end = Line.find("\"", start);
        if (end == std::string::npos)
            return "";
        Value = Line.substr(start , end - start);
        if (Value.empty())
            return "";
    }
    return Value;
}

parseResult logParser::nextEvent(Event &event)
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
            return EVENT_READ;
        }
        else
        {
            if (!parse(line, e))
            {
                std::cerr << "Error doing the parsing of the file\n";
                return PARSE_ERROR;
            }
        }
    }
    if (file.eof())
    {
        file.clear();
        return NO_EVENT;
    }
    return PARSE_ERROR;    
}
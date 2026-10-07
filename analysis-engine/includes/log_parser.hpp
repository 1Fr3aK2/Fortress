#ifndef LOG_PARSER_HPP
#define LOG_PARSER_HPP

#include <string>
#include <fstream>
#include <event.hpp>


enum parseResult
{
    EVENT_READ,
    NO_EVENT,
    PARSE_ERROR
};

class logParser
{
    private:
        std::ifstream file;
        bool parse(const std::string& Line, Event& Event);
        std::string parseLine(const std::string& Line, const std::string& Key);
    public:
        logParser(const std::string& Path);
        ~logParser();
        parseResult nextEvent(Event& event);
};

#endif
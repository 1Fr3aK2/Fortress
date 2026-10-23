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
        std::string path;
        std::ifstream file;
        Event current;
        bool inEvent;
        bool bad;
        bool parse(const std::string& Line, Event& ev);
    public:
        logParser(const std::string& Path);
        ~logParser();
        parseResult nextEvent(Event& event);
};

#endif
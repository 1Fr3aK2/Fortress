#ifndef LOG_PARSER_HPP
#define LOG_PARSER_HPP

#include <string>
#include <fstream>

class logParser
{
    private:
        std::ifstream file;
        bool parse(const std::string& line, Event& e);
        std::string parseLine(const std::string& line, const std::string& key);
    public:
        logParser(const std::string& path);
        ~logParser();
        bool nextEvent(Event &event);
};

#endif
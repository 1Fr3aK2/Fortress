#ifndef LOG_PARSER_HPP
#define LOG_PARSER_HPP

#include <string>
#include <fstream>

class logParser
{
    private:
        std::ifstream file;
    public:
        logParser(const std::string& path);
        ~logParser();
};

#endif
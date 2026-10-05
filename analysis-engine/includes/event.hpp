#ifndef EVENT_HPP
#define EVENT_HPP

#include <iostream>
#include <ctime>
#include <string>

struct Event
{
    time_t timestamp;
    std::string clientVersion;
    std::string srcIp;
    uint16_t port;
    std::string user;
    std::string password;
};



#endif
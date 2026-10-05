#ifndef EVENT_HPP
#define EVENT_HPP

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <map>
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
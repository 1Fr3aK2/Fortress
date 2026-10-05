#ifndef ATTACKER_PROFILE_HPP
#define ATTACKER_PROFILE_HPP

#include <vector>
#include <string>
#include <event.hpp>
#include <unordered_map>

struct attackerProfile
{
    size_t total;
    std::vector<time_t> timestamps;
    std::vector<std::string> clientVersion;
    std::vector<uint16_t> port;
    std::vector<std::string> user;
    std::vector<std::string> password;
    attackerProfile(const Event& event);
};


bool processEvents(const Event& event, std::unordered_map<std::string, attackerProfile>& Profile);
#endif
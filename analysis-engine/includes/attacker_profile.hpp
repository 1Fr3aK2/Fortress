#ifndef ATTACKER_PROFILE_HPP
#define ATTACKER_PROFILE_HPP

#include <vector>
#include <string>
#include <event.hpp>
#include <unordered_map>
#include <sliding_window.hpp>
#include <detection_engine.hpp>


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

struct attacker
{
    attackerProfile profile;
    slidingWindow window;
    attacker(const Event& event, time_t windowSize);
};


bool processEvents(const Event& event, std::unordered_map<std::string, attacker>& Profile, time_t windowSize, detectionEngine &Engine);
#endif
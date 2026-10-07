#ifndef ATTACKER_PROFILE_HPP
#define ATTACKER_PROFILE_HPP

#include <vector>
#include <string>
#include <event.hpp>
#include <unordered_map>
#include <sliding_window.hpp>
#include <detection_engine.hpp>
#include <alert_writer.hpp>


struct attackerProfile
{
    size_t total;
    std::vector<time_t> timestamps;
    std::vector<std::string> clientVersion;
    std::vector<uint16_t> port;
    std::vector<std::string> user;
    std::vector<std::string> password;
    attackerProfile(const Event& Event);
};

struct attacker
{
    attackerProfile profile;
    slidingWindow window;
    attacker(const Event& Event, time_t WindowSize);
};


bool processEvents(const Event& Event, std::unordered_map<std::string, attacker>& Profile, time_t WindowSize, detectionEngine &Engine, Alert& Alert);

#endif
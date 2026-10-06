#include <attacker_profile.hpp>
#include <unordered_map>
#include <sliding_window.hpp>
#include <detection_engine.hpp>

attackerProfile::attackerProfile(const Event& event)
{
    total = 1;
    timestamps.push_back(event.timestamp);
    clientVersion.push_back(event.clientVersion);
    port.push_back(event.port);
    user.push_back(event.user);
    password.push_back(event.password);
}

attacker::attacker(const Event& event, time_t windowSize) : profile(event), window(windowSize)
{
}

static void updateProfile(const Event& event, attackerProfile& attacker)
{
    attacker.total++;
    attacker.clientVersion.push_back(event.clientVersion);
    attacker.timestamps.push_back(event.timestamp);
    attacker.port.push_back(event.port);
    attacker.user.push_back(event.user);
    attacker.password.push_back(event.password);
}

bool processEvents(const Event& event, std::unordered_map<std::string, attacker>& Profile, time_t windowSize, detectionEngine& Engine)
{
    std::unordered_map<std::string, attacker>::iterator it;
    it = Profile.find(event.srcIp); 
    if (it == Profile.end())
    {
        attacker newAttacker(event, windowSize);
        newAttacker.window.addTimestamp(event.timestamp);
        try
        {
            it = Profile.insert(std::make_pair(event.srcIp, newAttacker)).first;
        }
        catch (const std::exception&)
        {
            return false;
        }
    }
    else
    {
        updateProfile(event, it->second.profile);
        it->second.window.addTimestamp(event.timestamp);
    }
    size_t occurrences = it->second.window.getOccurrences();
    Engine.checkBruteForce(occurrences);    
    return true;
}
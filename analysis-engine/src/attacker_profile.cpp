#include <attacker_profile.hpp>
#include <unordered_map>
#include <sliding_window.hpp>

attackerProfile::attackerProfile(const Event& event)
{
    total = 1;
    timestamps.push_back(event.timestamp);
    clientVersion.push_back(event.clientVersion);
    port.push_back(event.port);
    user.push_back(event.user);
    password.push_back(event.password);
}

attacker::attacker(const Event& event, size_t windowSize) : profile(event), window(windowSize)
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

bool processEvents(const Event& event, std::unordered_map<std::string, attacker>& Profile, size_t windowSize)
{
    std::unordered_map<std::string, attacker>::iterator it;
    it = Profile.find(event.srcIp); 
    if (it == Profile.end())
    {
        attacker newAttacker(event, windowSize);
        try
        {
            Profile.insert(std::make_pair(event.srcIp, newAttacker));
        }
        catch (const std::exception&)
        {
            return false;
        }
    }
    else
        updateProfile(event, it->second.profile);
    return true;
}
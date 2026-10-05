#include <attacker_profile.hpp>
#include <unordered_map>

attackerProfile::attackerProfile(const Event& event)
{
    total = 1;
    timestamps.push_back(event.timestamp);
    clientVersion.push_back(event.clientVersion);
    port.push_back(event.port);
    user.push_back(event.user);
    password.push_back(event.password);
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

bool processEvents(const Event& event, std::unordered_map<std::string, attackerProfile>& Profile)
{
    std::unordered_map<std::string, attackerProfile>::iterator it;
    it = Profile.find(event.srcIp); 
    if (it == Profile.end())
    {
        attackerProfile attacker(event);
        try
        {
            Profile.insert(std::make_pair(event.srcIp, attacker));
        }
        catch (const std::exception&)
        {
            return false;
        }
    }
    else
        updateProfile(event, it->second);
    return true;
}
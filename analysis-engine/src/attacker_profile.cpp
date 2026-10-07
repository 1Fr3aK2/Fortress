#include <attacker_profile.hpp>
#include <alert_writer.hpp>
#include <unordered_map>

attackerProfile::attackerProfile(const Event& Event)
{
    total = 1;
    timestamps.push_back(Event.timestamp);
    clientVersion.push_back(Event.clientVersion);
    port.push_back(Event.port);
    user.push_back(Event.user);
    password.push_back(Event.password);
}

attacker::attacker(const Event& Event, time_t WindowSize, time_t LastTimeSeen) : profile(Event), window(WindowSize), lastTimeSeen(LastTimeSeen)
{
}

static void updateProfile(const Event& Event, attackerProfile& Attacker)
{
    Attacker.total++;
    Attacker.clientVersion.push_back(Event.clientVersion);
    Attacker.timestamps.push_back(Event.timestamp);
    Attacker.port.push_back(Event.port);
    Attacker.user.push_back(Event.user);
    Attacker.password.push_back(Event.password);    
}

void removeInactiveIp(std::unordered_map<std::string, attacker>& Profile, time_t Timestamp, detectionEngine& Engine)
{
    std::unordered_map<std::string, attacker>::iterator it;
    for (it = Profile.begin(); it != Profile.end();)
    {
        if (Timestamp - it->second.lastTimeSeen >= INACTIVE)
        {
            Engine.removeAttacker(it->first);
            Profile.erase(it++);
        }
        else
            ++it;
    }
}

bool processEvents(const Event& Event, std::unordered_map<std::string, attacker>& Profile, time_t WindowSize, detectionEngine& Engine, Alert& Alert)
{
    std::unordered_map<std::string, attacker>::iterator it;
    it = Profile.find(Event.srcIp); 
    if (it == Profile.end())
    {
        attacker NewAttacker(Event, WindowSize, Event.timestamp);
        NewAttacker.window.addTimestamp(Event.timestamp);
        try
        {
            it = Profile.insert(std::make_pair(Event.srcIp, NewAttacker)).first;
        }
        catch (const std::exception&)
        {
            return false;
        }
    }
    else
    {
        updateProfile(Event, it->second.profile);
        it->second.window.addTimestamp(Event.timestamp);
        it->second.lastTimeSeen = Event.timestamp;
    }
    size_t Occurrences = it->second.window.getOccurrences();
    alertSeverity alertSeverity = Engine.checkBruteForce(Event.srcIp, Occurrences);
    if (alertSeverity == WARNING || alertSeverity == CRITICAL)
        Alert = buildAlert(Event.timestamp, it->first, it->second.window.WindowSize, Occurrences, alertSeverity);
    removeInactiveIp(Profile, Event.timestamp, Engine);
    return true;
}
#include <detection_engine.hpp>

detectionEngine::detectionEngine(){
}

detectionEngine::~detectionEngine(){
}

alertSeverity detectionEngine::checkBruteForce(const std::string& Ip, size_t Occurrences)
{
    if (Occurrences < BRUTE_FORCE_THRESHOLD)
        attackerAlert[Ip] = NONE;
    else if (Occurrences >= BRUTE_FORCE_CRITICAL_THRESHOLD)
    {
        if (attackerAlert[Ip] == CRITICAL)
            return NONE;
        attackerAlert[Ip] = CRITICAL;
    }
    else if (Occurrences >= BRUTE_FORCE_THRESHOLD)
    {
        if (attackerAlert[Ip] == WARNING)
            return NONE;
        attackerAlert[Ip] = WARNING;
    }
    return attackerAlert[Ip];
}

void detectionEngine::removeAttacker(const std::string& Ip)
{
    std::map<std::string, alertSeverity>::iterator it;
    it = attackerAlert.find(Ip);
    if (it != attackerAlert.end())
        attackerAlert.erase(it);
}
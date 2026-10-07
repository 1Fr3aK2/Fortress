#include <detection_engine.hpp>

detectionEngine::detectionEngine(){
}

detectionEngine::~detectionEngine(){
}

State detectionEngine::checkBruteForce(const std::string& Ip, size_t Occurrences)
{
    if (Occurrences < BRUTE_FORCE_THRESHOLD)
        attackerStates[Ip] = NONE;
    else if (Occurrences >= BRUTE_FORCE_CRITICAL_THRESHOLD)
    {
        if (attackerStates[Ip] == CRITICAL)
            return NONE;
        attackerStates[Ip] = CRITICAL;
    }
    else if (Occurrences >= BRUTE_FORCE_THRESHOLD)
    {
        if (attackerStates[Ip] == WARNING)
            return NONE;
        attackerStates[Ip] = WARNING;
    }
    return attackerStates[Ip];
}
#include <detection_engine.hpp>

detectionEngine::detectionEngine(){
}

detectionEngine::~detectionEngine(){
}

bool detectionEngine::checkBruteForce(size_t occurrences)
{
    if (occurrences >= BRUTE_FORCE_THRESHOLD)
        return true;
    return false;
}
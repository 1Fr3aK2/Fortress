#ifndef DETECTIONENGINE_HPP
#define DETECTIONENGINE_HPP

#include <string>
#include <map>

#define BRUTE_FORCE_THRESHOLD 5
#define BRUTE_FORCE_CRITICAL_THRESHOLD 20

enum State
{
    NONE,
    WARNING,
    CRITICAL
};

class detectionEngine
{
    private:
        std::map<std::string, State> attackerStates;
    public:
        detectionEngine();
        ~detectionEngine();
        State checkBruteForce(const std::string& Ip, size_t Occurrences);
};



#endif
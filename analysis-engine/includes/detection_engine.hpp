#ifndef DETECTIONENGINE_HPP
#define DETECTIONENGINE_HPP

#include <string>
#include <map>

#define BRUTE_FORCE_THRESHOLD 5
#define BRUTE_FORCE_CRITICAL_THRESHOLD 20

enum alertSeverity
{
    NONE,
    WARNING,
    CRITICAL
};

class detectionEngine
{
    private:
        std::map<std::string, alertSeverity> attackerAlert;
    public:
        detectionEngine();
        ~detectionEngine();
        alertSeverity checkBruteForce(const std::string& Ip, size_t Occurrences);
        void removeAttacker(const std::string& Ip);
};



#endif
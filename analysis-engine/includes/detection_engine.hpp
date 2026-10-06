#ifndef DETECTIONENGINE_HPP
#define DETECTIONENGINE_HPP

#include <string>

#define BRUTE_FORCE_THRESHOLD 5

class detectionEngine
{
    public:
        detectionEngine();
        ~detectionEngine();
        bool checkBruteForce(size_t occurrences);
};



#endif
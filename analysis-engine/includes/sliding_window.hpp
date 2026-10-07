#ifndef SLIDING_WINDOW_HPP
#define SLIDING_WINDOW_HPP

#include <deque>
#include <ctime>

struct slidingWindow
{
    time_t WindowSize;
    std::deque<time_t> timestamps;
    slidingWindow(time_t WindowSize);
    void addTimestamp(time_t Timestamp);
    size_t getOccurrences();
};


#endif

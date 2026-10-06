#ifndef SLIDING_WINDOW_HPP
#define SLIDING_WINDOW_HPP

#include <deque>
#include <string>
#include <ctime>
#include <event.hpp>

struct slidingWindow
{
    time_t WindowSize;
    std::deque<time_t> timestamps;
    slidingWindow(time_t windowSize);
    void addTimestamp(time_t timestamp);
};


#endif

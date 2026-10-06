#include <sliding_window.hpp>

slidingWindow::slidingWindow(time_t windowSize) : WindowSize(windowSize)
{
}

void slidingWindow::addTimestamp(time_t timestamp)
{
    timestamps.push_back(timestamp);
    while (timestamp - timestamps.front() > WindowSize)
        timestamps.pop_front();
}

size_t slidingWindow::getOccurrences()
{
    return(timestamps.size());
}
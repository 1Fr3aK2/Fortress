#include <sliding_window.hpp>

slidingWindow::slidingWindow(time_t WindowSize) : WindowSize(WindowSize)
{
}

void slidingWindow::addTimestamp(time_t Timestamp)
{
    timestamps.push_back(Timestamp);
    while (!timestamps.empty() && Timestamp - timestamps.front() > WindowSize)
        timestamps.pop_front();
}

size_t slidingWindow::getOccurrences()
{
    return(timestamps.size());
}
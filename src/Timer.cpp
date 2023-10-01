#include "Timer.hpp"

// Timer constructor.
Timer::Timer() = default;

// Starts timer.
void Timer::start()
{
    // clock_gettime() function gets the current time of the clock specified by clock_id.
    // CLOCK_MONOTONIC : High precision timer.
    clock_gettime(CLOCK_MONOTONIC, &start_time);
}

// Stops timer and returns total time (difference between end time - start time).
int Timer::stop()
{
    // Gets current time and calculates the total time by subtracting.
    clock_gettime(CLOCK_MONOTONIC, &end_time);
    double total_time = (end_time.tv_sec - start_time.tv_sec) * 1e9;

    // 1e-6 for milliseconds, 1e-9 for nanoseconds.
    total_time = (total_time + (end_time.tv_nsec - start_time.tv_nsec)) * 1e-6;

    // Returns time in ms.
    return static_cast<int>(total_time);
}

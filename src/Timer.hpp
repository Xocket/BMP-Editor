#ifndef TIMER_HPP
#define TIMER_HPP

#include <iostream>
#include <iomanip>

class Timer
{
private:
    // start_time and end_time struct definitions to hold time value.
    struct timespec start_time{};
    struct timespec end_time{};

public:
    // Timer constructor.
    Timer();

    // Function to start timer.
    void start();

    // Function to stop timer and return the difference.
    int stop();
};

#endif //TIMER_HPP

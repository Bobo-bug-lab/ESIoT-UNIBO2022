#ifndef __TIMER__
#define __TIMER__

#include <chrono>
#include <thread>
#include <iostream>

class Timer {
private:
    //bool timerFlag;
    std::chrono::high_resolution_clock::time_point m_start_time;
    int period;
    int frequency;
public:
    Timer();
    void setupFreq(int freq);
    void setupPeriod(int period);
    void waitForNextTick();
    bool check_time_since(long time_from, long period);
    std::string getCurrentTime();
    int getCurrentHour();
};

unsigned long millis();

#endif

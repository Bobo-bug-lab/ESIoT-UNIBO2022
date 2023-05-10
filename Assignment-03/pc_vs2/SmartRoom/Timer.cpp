#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <thread>
#include "Timer.h"
using namespace std;

    static auto start_time = std::chrono::high_resolution_clock::now(); // 保存程序开始时间

    unsigned long millis() {
    auto current_time = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(current_time - start_time).count();
    }
    
    Timer::Timer() {
        this->frequency = 100;
    }
    
    void Timer::setupFreq(int freq) {
        this->frequency = freq;
    }
    void Timer::setupPeriod(int per) {
        this->period = per;
    }
    void Timer::waitForNextTick() {
        // wait for the next tick by sleeping for the remaining time
        auto now = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(now - m_start_time);
        auto remaining = std::chrono::microseconds(1000000 / this->frequency ) - elapsed; // assuming 100 Hz frequency
        if (remaining > std::chrono::microseconds::zero()) {
            std::this_thread::sleep_for(remaining);
        }
        m_start_time = std::chrono::high_resolution_clock::now();
    }
    bool Timer::check_time_since(long time_from, long period) {
        auto now = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - std::chrono::high_resolution_clock::time_point(std::chrono::milliseconds(time_from)));
        return elapsed.count() >= period;
    }
    string Timer::getCurrentTime() {
        auto now = std::chrono::system_clock::now();
        auto time_now = std::chrono::system_clock::to_time_t(now);

        std::stringstream ss;
        ss << std::put_time(std::localtime(&time_now), "%Y-%m-%d %H:%M:%S");
        return ss.str();
    }

    int Timer::getCurrentHour() {
        auto now = std::chrono::system_clock::now();
        auto time_now = std::chrono::system_clock::to_time_t(now);

        return std::localtime(&time_now)->tm_hour;
    };




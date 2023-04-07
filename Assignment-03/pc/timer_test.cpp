#include <iostream>
#include <chrono>
#include <thread>
#include "Timer.h"
using namespace std;

int main() {
    Timer timer;
    std::cout << "Setting up timer with 100 Hz frequency..." << std::endl;
    timer.setupFreq(100);
    std::cout << "Waiting for 10 ticks..." << std::endl;
    for (int i = 0; i < 10; i++) {
        timer.waitForNextTick();
        std::cout << "Tick " << i+1 << std::endl;
    }

    std::cout << "Setting up timer with 500 ms period..." << std::endl;
    timer.setupPeriod(500);
    std::cout << "Waiting for 5 ticks..." << std::endl;
    for (int i = 0; i < 5; i++) {
        timer.waitForNextTick();
        std::cout << "Tick " << i+1 << std::endl;
        cout << "Current hour is: " << timer.getCurrentHour() << std::endl;
        cout << "Current time is: " << timer.getCurrentTime() << std::endl;
    }

    std::cout << "Testing check_time_since..." << std::endl;
    long start_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    for (int i = 0; i < 10; i++) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        bool timed_out = timer.check_time_since(start_time, 500);
        if (timed_out) {
            std::cout << "Timeout occurred at tick " << i+1 << std::endl;
            break;
        }
        cout << "Tick " << i+1 << std::endl;

    }

    system("PAUSE");
    return 0;
}
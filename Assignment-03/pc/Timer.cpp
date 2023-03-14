#include <chrono>
#include <thread>

class Timer {
private:
    std::chrono::high_resolution_clock::time_point m_start_time;
public:
    Timer() {}
    void setupFreq(int freq) {
        // do nothing, as there is no hardware timer on PC
    }
    void setupPeriod(int period) {
        // do nothing, as there is no hardware timer on PC
    }
    void waitForNextTick() {
        // wait for the next tick by sleeping for the remaining time
        auto now = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(now - m_start_time);
        auto remaining = std::chrono::microseconds(1000000 / 100) - elapsed; // assuming 100 Hz frequency
        if (remaining > std::chrono::microseconds::zero()) {
            std::this_thread::sleep_for(remaining);
        }
        m_start_time = std::chrono::high_resolution_clock::now();
    }
    bool check_time_since(long time_from, long period) {
        auto now = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - std::chrono::high_resolution_clock::time_point(std::chrono::milliseconds(time_from)));
        return elapsed.count() >= period;
    }
};
#ifndef TIMER_H
#define TIMER_H

#include <chrono>

/***********************************************************************************/
class Timer {

public:
    Timer() = default;

    Timer(Timer&&) = default;
    Timer(const Timer&) = delete;
    Timer& operator=(Timer&&) = default;
    Timer& operator=(const Timer&) = delete;

    void update();

    double getDelta();

    auto getFrameTime() {
        return getDelta() * 1000.0;
    }

private:
    using time_point = std::chrono::high_resolution_clock::time_point;

    time_point m_prevTimePoint, m_currTimePoint;

    std::chrono::duration<double> m_delta;
};

#endif // TIMER_H

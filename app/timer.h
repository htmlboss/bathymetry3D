#pragma once

#include <chrono>

/***********************************************************************************/
class Timer {
	using time_point = std::chrono::high_resolution_clock::time_point;
public:
    Timer() = default;
	~Timer() = default;

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

    time_point m_prevTimePoint, m_currTimePoint;

    std::chrono::duration<double> m_delta{ 0.0 };
};

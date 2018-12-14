#include "timer.h"

using namespace std::chrono;

/***********************************************************************************/
void Timer::update() {
    m_prevTimePoint = m_currTimePoint;
    m_currTimePoint = high_resolution_clock::now();
}

/***********************************************************************************/
double Timer::getDelta() {
    m_delta = duration_cast<duration<double>>(m_currTimePoint - m_prevTimePoint);

    return m_delta.count();
}

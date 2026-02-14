//
// Created by aglorice on 2026/2/14.
//

#include "timer.h"

using namespace yazi::timer;

Timer::Timer() : m_period(0),m_repeat(-1) {
    m_time = now();
}

Timer::Timer(int repeat) : m_period(0),m_repeat(repeat) {
    m_time = now();
}

Timer::~Timer() {

}


void Timer::on_timer() {
    if (!m_func || m_repeat==0) {
        return;
    }
    m_func();
    m_time += m_period;
    if (m_repeat > 0) {
        m_repeat--;
    }
}

int64_t Timer::now() {
    auto now = std::chrono::system_clock::now();
    // 将时间戳转化为毫秒数
    auto now_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(now);
    return now_ms.time_since_epoch().count();
}


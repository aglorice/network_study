//
// Created by aglorice on 2026/2/14.
//

#include "timer.h"

using namespace yazi::utility;

Timer::Timer(): m_active(false),m_period(0),m_repeat(-1) {
    //repeat = -1 无限周期执行

}

Timer::Timer(int repeat): m_active(false),m_period(0),m_repeat(repeat) {

}

Timer::~Timer() {
    stop();
}

void Timer::stop() {
    m_active.store(false);
}




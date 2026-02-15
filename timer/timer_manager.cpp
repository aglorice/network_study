//
// Created by aglorice on 2026/2/15.
//

#include "timer_manager.h"

using namespace yazi::timer;

void TimerManager::update() {
    if (m_timers.empty()) {
        return;
    }
    int64_t now = Timer::now();
    for (auto it = m_timers.begin();it != m_timers.end();) {
        if (it->first > now) {
            return;
        }
        it->second.on_timer();
        Timer t = it->second;
        it = m_timers.erase(it);
        if (t.m_repeat != 0) {
            auto new_it = m_timers.insert(std::make_pair(t.m_time,t));
            if (it == m_timers.end() || new_it->first < it->first) {
                it = new_it;
            }
        }
    }
}

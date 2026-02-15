//
// Created by aglorice on 2026/2/14.
//

#ifndef NETWORK_STUDY_TIMER_H
#define NETWORK_STUDY_TIMER_H
#include <functional>
#include <chrono>
namespace yazi {
    namespace timer {
        class Timer {
            friend class TimerManager;
        public:
            Timer();
            Timer(int repeat);
            ~Timer();

            static int64_t now();

            template<typename F,typename... Args>
            void callback(int milliseconds,F &&f,Args&&... args);

            void on_timer();
        private:
            int64_t m_time; // 以毫米为单位
            std::function<void()> m_func;
            int m_period; // 定时触发的事件点
            int m_repeat; // 定时器触发的次数，-1表示无限触发
        };

        template<typename F, typename... Args>
        void Timer::callback(int milliseconds, F &&f, Args &&... args) {
            m_period = milliseconds;
            m_func = std::bind(std::forward<F>(f),std::forward<Args>(args)...);

        }

    }
}

#endif //NETWORK_STUDY_TIMER_H
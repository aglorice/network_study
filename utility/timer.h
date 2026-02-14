//
// Created by aglorice on 2026/2/14.
//

#ifndef NETWORK_STUDY_TIMER_H
#define NETWORK_STUDY_TIMER_H
#include <thread>
#include <atomic>
#include <functional>

namespace yazi {
    namespace utility {
        class Timer {
        public:
            Timer();
            Timer(int repeat);
            ~Timer();

            // 启动定时任务
            template<typename F,typename... Args>
            void start(int millisecond,F && func,Args&&... args);
            // 关闭定时任务
            void stop();

        private:
            std::thread m_thread;
            std::atomic<bool> m_active;
            std::function<void()> m_func;
            int m_period; // millisecond;
            int m_repeat; // 触发的次数，-1表示无限执行
        };

        template<typename F, typename... Args>
        void Timer::start(int millisecond, F &&func, Args &&... args) {
            if (m_active.load()) {
                return;
            }
            m_period = millisecond;
            m_func = std::bind(std::forward<F>(func),std::forward<Args>(args)...);
            m_active.store(true); // 保证这一操作的原子性
            m_thread = std::thread([&]() {
                if (m_repeat < 0) {
                    while (m_active.load()) {
                        std::this_thread::sleep_for(std::chrono::milliseconds(m_period));
                        if (!m_active.load()) {
                            return;
                        }
                        m_func();
                    }
                }else {
                    while (m_repeat > 0) {
                        if (!m_active.load()) {
                            return;
                        }
                        std::this_thread::sleep_for(std::chrono::milliseconds(m_period));
                        if (!m_active.load()) {
                            return;
                        }
                        m_func();
                        m_repeat--;
                    }
                }
            });
            m_thread.detach(); // 分离该线程
        }

    }
}



#endif //NETWORK_STUDY_TIMER_H
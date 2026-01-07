//
// Created by aglorice on 2025/12/19.
//

#ifndef NETWORK_STUDY_TIME_H
#define NETWORK_STUDY_TIME_H
#include <ctime>
#include <string>
#ifdef WIN32
#include <windows.h>
#else
#include <sys/time.h>
#include <unistd.h>
#endif
namespace yazi {
    namespace utility {
        class Time {
        public:
            Time();
            ~Time() = default;

            int year() const;
            int month() const;
            int day() const;

            int hour() const;
            int min() const;
            int second() const;

            int week() const;

            void show() const;

            double seconds() const;
            double milliseconds() const;

            double operator-(const Time & other) const;

            static void sleep(int milliseconds);

            std::string format(const std::string & format) const;
        private:
            void get_local_time(struct tm * tm,const time_t * ticks);
            void get_time_of_day(struct timeval *tv);
        private:
            struct tm m_tm = {0};
            int m_sec;
            int m_usec;
        };
    }
}
#endif //NETWORK_STUDY_TIME_H
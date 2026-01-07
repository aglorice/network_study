//
// Created by aglorice on 2025/12/19.
//
#include <sys/time.h>

#include "value.h"
#include "time.h"

using namespace yazi::utility;


Time::Time() {
    time_t ticks = time(nullptr);

    get_local_time(&m_tm,&ticks);

    struct timeval tv = {};
    get_time_of_day(&tv);
    m_sec = tv.tv_sec;
    m_usec =  tv.tv_usec;
}

void Time::get_local_time(struct tm *tm, const time_t *ticks) {
#ifdef WIN32
    localtime_s(tm,ticks)
#else
    localtime_r(ticks,tm);
#endif
}


void Time::get_time_of_day(struct timeval *tv) {
#ifdef WIN32
    SYSTEMTIME wtm;
    GetLocalTime(&wtm);
    struct tm tm;
    tm.tm_year = wtm.wYear-1900;
    tm.tm_mon = wtm.wMonth - 1;
    tm.tm_mday = wtm.wDay;
    tm.tm_hour = wtm.wHour;
    tm.tm_min = wtm.wMinute;
    tm.tm_sec = wtm.wSecond;
    tm.tm_isdst = -1;
    time_t ticks = mktime(&tm);
    tv->tv_sec = ticks;
    tv->tv_usec = wtm.wMilliseconds * 1000;
#else
    gettimeofday(tv,nullptr);
#endif
}


int Time::year() const {
    return m_tm.tm_year + 1900;
}

int Time::month() const {
    return m_tm.tm_mon + 1;
}

int Time::day() const {
    return m_tm.tm_mday;
}

int Time::hour() const {
    return m_tm.tm_hour;
}

int Time::min() const {
    return m_tm.tm_min;
}

int Time::second() const {
    return m_tm.tm_sec;
}

int Time::week() const {
    return m_tm.tm_wday;
}

void Time::show() const {
    std::cout << year() << "-" << month() << "-" << day() << " " << hour() << ":" << min() << ":" << second() <<std::endl;
}

double Time::seconds() const {
    return m_sec;
}

double Time::milliseconds() const {
    return m_sec * 1000 + m_usec/1000.0;
}

double Time::operator-(const Time &other) const {
    return (m_sec-other.m_sec)*1000000 + (m_usec-other.m_usec);
}

void Time::sleep(const int milliseconds) {
#ifdef WIN32
    Sleep(milliseconds);
#else
    usleep(milliseconds*1000);
#endif
}

std::string Time::format(const std::string &format) const {
    char timestamp[32] = {0};
    strftime(timestamp,sizeof(timestamp),format.c_str(),&m_tm);
    return timestamp;
}













//
// Created by aglorice on 2026/2/19.
//

#include "selector.h"

#include <sys/_types/_fd_zero.h>

using namespace yazi::socket;

Selector::Selector() : m_maxfd(0) {
    FD_ZERO(&m_fds);
    FD_ZERO(&m_read_fds);
}

Selector::~Selector() {
    FD_ZERO(&m_fds);
    FD_ZERO(&m_read_fds);
    m_maxfd = 0;
}

void Selector::set(int fd) {
    FD_SET(fd,&m_fds);
    if (m_maxfd < fd) {
        m_maxfd = fd;
    }
}

void Selector::del(int fd) {
    FD_CLR(fd,&m_fds);
}

bool Selector::is_set(int fd) {
    return FD_ISSET(fd,&m_read_fds);
}

int Selector::select(int milliseconds) {
    struct timeval tv;
    tv.tv_sec = milliseconds / 1000;
    tv.tv_usec = (milliseconds % 1000) * 1000;

    m_read_fds = m_fds;
    return ::select(m_maxfd+1,&m_read_fds,nullptr,nullptr,&tv);
}

int Selector::max_fd() {
    return m_maxfd;
}








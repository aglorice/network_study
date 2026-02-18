//
// Created by aglorice on 2026/2/17.
//

#include "socket.h"

using namespace yazi::socket;

Socket::Socket() :m_ip(""),m_port(0),m_sock_fd(0) {
    m_sock_fd = ::socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if (m_sock_fd < 0) {
        log_error("create socket error: errno = %d errmsg = %s",errno,strerror(errno));
    }else {
        log_debug("create socket success!");
    }
}

Socket::Socket(int sock_fd) : m_ip(""),m_port(0),m_sock_fd(sock_fd) {

}


bool Socket::bind(const std::string &ip,int port) {
    struct sockaddr_in sockaddr{};
    std::memset(&sockaddr,0,sizeof(sockaddr));
    sockaddr.sin_family = AF_INET;
    if (ip.empty()) {
        sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    }else {
        sockaddr.sin_addr.s_addr = inet_addr(ip.c_str());
    }
    sockaddr.sin_port = htons(port);

    if (::bind(m_sock_fd,(struct sockaddr *)&sockaddr,sizeof(sockaddr)) < 0) {
        log_error("socket bind error: errno = %d errmsg = %s",errno,strerror(errno));
        return false;
    }else {
        log_debug("socket bind success: ip=%s port = %d sock_fd = %d",ip.c_str(),port,m_sock_fd);
    }
    m_ip = ip;
    m_port = port;
    return true;
}

bool Socket::listen(int backlog) {
    if (::listen(m_sock_fd,backlog) < 0) {
        log_error("socket listen error: errno = %d errmsg = %s",errno,strerror(errno));
        return false;
    }else {
        log_debug("socket listening...");
    }
    return true;
}

bool Socket::connect(const std::string &ip,int port) {
    struct sockaddr_in sockaddr{};
    std::memset(&sockaddr,0,sizeof(sockaddr));
    sockaddr.sin_family = AF_INET;
    sockaddr.sin_addr.s_addr = inet_addr(ip.c_str());
    sockaddr.sin_port = htons(port);
    if (::connect(m_sock_fd,(struct sockaddr*)&sockaddr,sizeof(sockaddr))<0) {
        log_error("socket connect error: errno = %d, errmsg=%s",errno,strerror(errno));
        return false;
    }
    m_ip = ip;
    m_port = port;
    return true;
}

int Socket::accept() {
    int conn_fd = ::accept(m_sock_fd,nullptr,nullptr);
    if (conn_fd < 0) {
        log_error("socket accept error: errno = %d errmsg = %s",errno,strerror(errno));
        return -1;
    }
    log_debug("scoket accept: conn=%d",conn_fd);
    return conn_fd;
}

int Socket::send(const char * buf,int len) {
    return  ::send(m_sock_fd,buf,len,0);
}

int Socket::recv(char *buf,int len) {
    return ::recv(m_sock_fd,buf,len,0);
}

void Socket::close() {
    if (m_sock_fd > 0) {
        ::close(m_sock_fd);
        m_sock_fd = 0;
    }
}

bool Socket::set_non_blocking() {
    int flags = fcntl(m_sock_fd,F_GETFL,0);
    if (flags < 0) {
        log_error("socket set_non_blocking error: errno=%d, errmsg=%s",errno,strerror(errno));
        return false;
    }
    flags |= O_NONBLOCK;
    if (fcntl(m_sock_fd,F_SETFL,flags)<0) {
        log_error("socket set_non_blocking error: errno=%d, errmsg=%s",errno,strerror(errno));
        return true;
    }
    return true;
}

bool Socket::set_send_buffer(int size) {
    int buff_size = size;
    if (setsockopt(m_sock_fd,SOL_SOCKET,SO_SNDBUF,&buff_size,sizeof(buff_size))<0) {
        log_error("socket set_send_buffer error: error=%d, errmsg=%s",errno,strerror(errno));
        return false;
    }
    return true;
}

bool Socket::set_recv_buffer(int size) {
    int buff_size = size;
    if (setsockopt(m_sock_fd,SOL_SOCKET,SO_RCVBUF,&buff_size,sizeof(buff_size))<0) {
        log_error("socket set_recv_buffer error: error=%d, errmsg=%s",errno,strerror(errno));
        return false;
    }
    return true;
}

bool Socket::set_linger(bool active,int seconds) {
    struct linger l;
    std::memset(&l,0,sizeof(l));
    l.l_onoff = active ? 1:0;
    l.l_linger = seconds;
    if (setsockopt(m_sock_fd,SOL_SOCKET,SO_LINGER,&l,sizeof(l))<0) {
        log_error("socket set_linger error: errno=%d errmsg=%s",errno,strerror(errno));
        return false;
    }
    return true;
}

bool Socket::set_keepalive() {
    int flag = 1;
    if (setsockopt(m_sock_fd,SOL_SOCKET,SO_KEEPALIVE,&flag,sizeof(flag))<0) {
        log_error("socket set_keepalive error: errno=%d errmsg=%s",errno,strerror(errno));
        return false;
    }
    return true;
}

bool Socket::set_reuse_addr() {
    int flag = 1;
    if (setsockopt(m_sock_fd,SOL_SOCKET,SO_REUSEADDR,&flag,sizeof(flag))<0) {
        log_error("socket set_reuse_addr error: errno=%d errmsg=%s",errno,strerror(errno));
        return false;
    }
    return true;
}

Socket::~Socket() {
    close();
}


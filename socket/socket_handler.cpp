//
// Created by aglorice on 2026/2/20.
//
#include "socket_handler.h"

#include "../task/echo_task.h"

using namespace yazi::socket;
using namespace yazi::task;



void SocketHandler::listen(const std::string &ip, int port) {
    m_server = new ServerSocket(ip,port);
}


void SocketHandler::attach(int sock_fd) {
    m_selector.set(sock_fd);
}

void SocketHandler::detach(int sock_fd) {
    m_selector.del(sock_fd);
}

void SocketHandler::handle(int timeout) {
    attach(m_server->fd());
    while (true) {
        int ret = m_selector.select(timeout);
        if (ret < 0) {
            log_error("select error: errno = %d, errmsg = %s",errno,strerror(errno));
            break;
        }else if (ret == 0) {
            log_error("select timeout");
            continue;
        }
        log_debug("select ok: ret=%d",ret);
        for (int fd = 0; fd<m_selector.max_fd()+1;fd++) {
            if (!m_selector.is_set(fd)) {
                continue;
            }
            if (fd == m_server->fd()) {
                // 如果是服务端套接字可读
                int connfd = m_server->accept();
                if (connfd < 0) {
                    continue;
                }
                Socket socket(connfd);
                socket.set_non_blocking();
                attach(connfd);
            }else {
                // 否则客户端套接字可读
                detach(fd);

                EchoTask task(fd);
                if (!task.run()) {
                    ::close(fd);
                }else {
                    attach(fd);
                }
            }
        }
    }
}



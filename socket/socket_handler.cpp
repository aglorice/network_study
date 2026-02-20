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


void SocketHandler::attach(Socket *socket) {
    m_selector.set(socket->fd());
    m_conn[socket->fd()] = socket;
}

void SocketHandler::detach(Socket *socket) {
    m_selector.del(socket->fd());
}

void SocketHandler::remove(Socket *socket) {
    detach(socket);
    socket->close();
    auto it = m_conn.find(socket->fd());
    if (it!=m_conn.end()) {
        m_conn.erase(it);
    }
    delete socket;
}

void SocketHandler::handle(int timeout) {
    attach(m_server);
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
                auto socket = new Socket(connfd);
                attach(socket); // 处理逻辑的时候就先将这个socket移除监听队列；
            }else {
                // 否则客户端套接字可读
                auto socket = m_conn[fd];
                detach(socket);

                EchoTask task(socket);
                if (!task.run()) {
                    remove(socket);
                }else {
                    attach(socket);
                }
            }
        }
    }
}



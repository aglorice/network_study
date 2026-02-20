//
// Created by aglorice on 2026/2/20.
//

#include "echo_task.h"

using namespace yazi::task;

EchoTask::EchoTask(int sock_fd) : m_sock_fd(sock_fd) {

}

void EchoTask::destroy() {
    log_debug("echo task destroy");
}

bool EchoTask::run() {
    log_debug("echo task run");
    Socket socket(m_sock_fd);
    char buf[1024] = {0};

    int len = socket.recv(buf,sizeof(buf));
    if (len < 0) {
        if (errno == EAGAIN || errno == EWOULDBLOCK) {
            log_error("socket recv/send would block: conn=%d",m_sock_fd);
            return true;
        }
        else if (errno == EINTR) {
            log_error("socket recv interrupted: conn=%d",m_sock_fd);
            return true;
        }
        log_error("socket connection abort: conn=%d",m_sock_fd);
        return false;
    }
    if (len == 0) {
        log_error("socket closed by peer: conn=%d",m_sock_fd);
        return false;
    }else if (len > 0) {
        log_debug("recv: conn=%d, msg=%s",m_sock_fd,buf);
        // 向客户端发送信息
        log_debug("send: conn=%d, msg=%s",m_sock_fd,buf);
        socket.send(buf,len);
    }
    return true;
}

EchoTask::~EchoTask() {
    destroy();
}




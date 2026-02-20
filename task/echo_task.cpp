//
// Created by aglorice on 2026/2/20.
//

#include "echo_task.h"

using namespace yazi::task;

EchoTask::EchoTask(Socket *socket) : m_socket(socket) {

}

void EchoTask::destroy() {
    log_debug("echo task destroy");
}

bool EchoTask::run() {
    log_debug("echo task run");

    char buf[1024] = {0};
    size_t len = m_socket->recv(buf,sizeof(buf));
    if (len == 0) {
        log_error("socket closed by peer: conn=%d",m_socket->fd());
        // FD_CLR(fd,&fds);
        return false;
    }else if (len > 0) {
        log_debug("recv: conn=%d, msg=%s",m_socket->fd(),buf);
        // 向客户端发送信息
        log_debug("send: conn=%d, msg=%s",m_socket->fd(),buf);
        m_socket->send(buf,len);
    }
    return true;
}

EchoTask::~EchoTask() {
    destroy();
}




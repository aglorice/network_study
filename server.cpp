//
// Created by aglorice on 2026/2/17.
//

#include "socket/server_socket.h"
#include "socket/selector.h"
#include <sys/select.h>

using namespace yazi::socket;

int main() {
    Singleton<Logger>::instance()->open("./../server.log");
    ServerSocket server_socket("127.0.0.1",8080);

    // fd_set fds;
    // FD_ZERO(&fds);
    // // 监听服务端的套接字
    // FD_SET(server_socket.fd(),&fds);
    // int max_fd = server_socket.fd();
    Selector selector;
    selector.set(server_socket.fd());

    while (true) {
        int ret = selector.select(2000);
        if (ret < 0) {
            log_error("select error: errno = %d, errmsg = %s",errno,strerror(errno));
            break;
        }else if (ret == 0) {
            log_error("select timeout");
            continue;
        }
        log_debug("select ok: ret=%d",ret);
        for (int fd = 0; fd<selector.max_fd()+1;fd++) {
            if (!selector.is_set(fd)) {
                continue;
            }
            if (fd == server_socket.fd()) {
                // 如果是服务端套接字可读
                int connfd = server_socket.accept();
                if (connfd < 0) {
                    return 1;
                }
                selector.set(connfd);
            }else {
                // 否则客户端套接字可读
                Socket client(fd);

                char buf[1024] = {0};
                size_t len = client.recv(buf,sizeof(buf));
                if (len == 0) {
                    log_error("socket closed by peer: conn=%d",fd);
                    // FD_CLR(fd,&fds);
                    selector.del(fd);
                    client.close();
                }else if (len > 0) {
                    log_debug("recv: conn=%d, msg=%s",fd,buf);

                    // 向客户端发送信息
                    client.send(buf,len);
                    client.clear(); // 避免析构函数被调用导致套接字被关闭
                }
            }
        }
    }
    return 0;
}

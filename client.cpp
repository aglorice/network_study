//
// Created by aglorice on 2026/2/17.
//
//
// Created by aglorice on 2026/2/17.
//

#include "socket/client_socket.h"

using namespace yazi::socket;

int main() {
    Singleton<Logger>::instance()->open("./../client.log");


    ClientSocket client_socket("127.0.0.1",8080);

    std::string data = "hello world";
    client_socket.send(data.c_str(),data.size());



    // 接收来自服务端的数据
    char buf[1024] = {0};
    client_socket.recv(buf,sizeof(buf));
    log_info("recv: %s",buf);
    return 0;
}

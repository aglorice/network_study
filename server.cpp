//
// Created by aglorice on 2026/2/17.
//


#include "socket/socket_handler.h"

using namespace yazi::socket;

int main() {
    Singleton<Logger>::instance()->open("./../server.log");

    Singleton<SocketHandler>::instance()->listen("127.0.0.1",8080);
    Singleton<SocketHandler>::instance()->handle(2000);
    return 0;
}

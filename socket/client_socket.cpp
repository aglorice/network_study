//
// Created by aglorice on 2026/2/18.
//
#include "client_socket.h"

using namespace yazi::socket;

ClientSocket::ClientSocket(const std::string &ip, int port) : Socket() {
    connect(ip,port);
}

//
// Created by aglorice on 2026/2/18.
//

#ifndef NETWORK_STUDY_SERVER_SOCKET_H
#define NETWORK_STUDY_SERVER_SOCKET_H
#include "socket.h"

namespace yazi {
    namespace socket {
        class ServerSocket : public Socket{
        public:
            ServerSocket() = delete;
            ServerSocket(const std::string &ip,int port);
            ~ServerSocket() = default;
        };
    }
}

#endif //NETWORK_STUDY_SERVER_SOCKET_H
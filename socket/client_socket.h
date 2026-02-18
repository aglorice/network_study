//
// Created by aglorice on 2026/2/18.
//

#ifndef NETWORK_STUDY_CLIENT_SOCKET_H
#define NETWORK_STUDY_CLIENT_SOCKET_H
#include "socket.h"
using namespace yazi::socket;

namespace yazi {
    namespace socket {
        class ClientSocket : public Socket{
        public:
            ClientSocket() = delete;
            ClientSocket(const std::string &ip,int port);
            ~ClientSocket() = default;
        };
    }
}
#endif //NETWORK_STUDY_CLIENT_SOCKET_H
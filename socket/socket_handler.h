//
// Created by aglorice on 2026/2/20.
//

#ifndef NETWORK_STUDY_SOCKET_HANDLER_H
#define NETWORK_STUDY_SOCKET_HANDLER_H
#include <map>
#include "selector.h"
#include "socket.h"
#include "server_socket.h"

namespace yazi {
    namespace socket {
        class SocketHandler {
            SINGLETON(SocketHandler);
        public:

            void listen(const std::string &ip,int port);
            void attach(Socket *socket);
            void detach(Socket* socket);
            void remove(Socket *socket);
            void handle(int timeout);
        private:
            Socket * m_server = nullptr;
            Selector m_selector;
            std::map<int,Socket*> m_conn;
        };
    }
}

#endif //NETWORK_STUDY_SOCKET_HANDLER_H
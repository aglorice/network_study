//
// Created by aglorice on 2026/2/17.
//

#ifndef NETWORK_STUDY_SOCKET_H
#define NETWORK_STUDY_SOCKET_H

#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <fcntl.h>

#include "../utility/logger.h"

using namespace yazi::utility;

namespace yazi {
    namespace socket {
        class Socket {
        public:
            Socket();
            Socket(int sock_fd);
            virtual ~Socket();

            int fd() const;

            bool bind(const std::string &ip,int port);
            bool listen(int backlog);
            bool connect(const std::string&ip,int port);
            int accept();

            int send(const char *buf,int len);
            int recv(char *buf,int len);

            void close();
            void clear();

            bool set_non_blocking();
            bool set_send_buffer(int size);
            bool set_recv_buffer(int size);
            bool set_linger(bool active,int seconds);
            bool set_keepalive();
            bool set_reuseaddr();

        protected:
            std::string m_ip;
            int m_port;
            int m_sock_fd;
        };
    }
}

#endif //NETWORK_STUDY_SOCKET_H
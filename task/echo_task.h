//
// Created by aglorice on 2026/2/20.
//

#ifndef NETWORK_STUDY_ECHO_TASK_H
#define NETWORK_STUDY_ECHO_TASK_H

#include "../socket/socket.h"

using namespace yazi::socket;

namespace yazi {
    namespace task {
        class EchoTask {
        public:
            EchoTask() = delete;
            EchoTask(int sock_fd);
            ~EchoTask();

            bool run();
            void destroy();

        private:
            int m_sock_fd = 0;
        };
    }
}

#endif //NETWORK_STUDY_ECHO_TASK_H
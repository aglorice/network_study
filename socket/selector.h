//
// Created by aglorice on 2026/2/19.
//

#ifndef NETWORK_STUDY_SELECTOR_H
#define NETWORK_STUDY_SELECTOR_H
#include <sys/select.h>

namespace yazi {
    namespace socket {
        class Selector {
        public:
            Selector();
            ~Selector();

            void set(int fd);
            void del(int fd);
            int select(int milliseconds);
            int max_fd();
            bool is_set(int fd);
        private:
            fd_set m_fds;
            fd_set m_read_fds;
            int m_maxfd;
        };
    }
}

#endif //NETWORK_STUDY_SELECTOR_H
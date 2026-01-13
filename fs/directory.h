//
// Created by aglorice on 2026/1/13.
//

#ifndef NETWORK_STUDY_DIRECTORY_H
#define NETWORK_STUDY_DIRECTORY_H
#include <string>

namespace yazi {
    namespace fs {
        class Directory {
        public:
            Directory();
            Directory(const std::string &path);
            ~Directory() = default;

            // 获取目录的路径
            std::string path() const;
        private:
            std::string m_path;
        };
    }
}

#endif //NETWORK_STUDY_DIRECTORY_H
//
// Created by aglorice on 2026/1/13.
//

#ifndef NETWORK_STUDY_DIRECTORY_H
#define NETWORK_STUDY_DIRECTORY_H
#include <string>
#include "../utility/string.h"
#include <iostream>
#include <algorithm>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
using namespace yazi::utility;

namespace yazi {
    namespace fs {
        class Directory {
        public:
            Directory();
            Directory(const std::string &path);
            ~Directory() = default;

            // 获取目录的路径
            std::string path() const;

            // 创建一个空目录（含子目录）
            bool create();

            // 判断一个目录是否存在
            bool exists() const;

            // 删除一个目录
            bool remove() const;

        public:
            // 获取路径的分隔符
            static char separator();

            static bool is_absolute_path(const std::string &path);

            static std::string normalize_path(const std::string &path);

            static std::string adjust_path(const std::string & path);
        private:
            std::string m_path;
        };
    }
}

#endif //NETWORK_STUDY_DIRECTORY_H
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
#include "file.h"
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
            bool remove();

            // 清空一个目录
            void clear();

            // 目录的重命名
            bool rename(const std::string &path);

            // 复制目录
            bool copy(const std::string &path);

            // 获取一个目录下的所有文件
            std::vector<File> file() const;

            // 获取目录下包含文件的数量
            int count() const;

            // 获取目录下以及子目录文件的行数
            int line() const;

            long size() const;


        public:
            // 获取路径的分隔符
            static char separator();

            static bool is_absolute_path(const std::string &path);

            static std::string normalize_path(const std::string &path);

            static std::string adjust_path(const std::string & path);

            int mkdir(const char * path);
            int rmdir(const char * path);
            int unlink(const char * path);
            static char *getcwd(char *buf, int len);
        private:
            std::string m_path;
        };
    }
}

#endif //NETWORK_STUDY_DIRECTORY_H
//
// Created by aglorice on 2026/1/10.
//

#ifndef NETWORK_STUDY_FILE_H
#define NETWORK_STUDY_FILE_H
#include <string>
#include <cstdio>
#include <fstream>
#include <sys/stat.h>
#include <iostream>
#include <sstream>

namespace yazi {
    namespace fs {
        class File {
        public:
            File() = delete;
            File(const std::string &path);
            ~File() = default;

            // 获取文件路径
            [[nodiscard]] const std::string path() const;

            // 获取文件所在目录
            [[nodiscard]]const std::string dir() const;

            // 创建一个文件
            bool create();

            // 删除文件
            bool remove();

            // 修改文件名
            bool rename(const std::string &path);

            // 清空文件
            void clear();

            // 判断文件是否存在
            [[nodiscard]] bool exists() const;

            // 复制文件
            bool copy(const std::string &path);

            // 获取文件的行数
            [[nodiscard]] int line() const;

            // 获取文件最后修改的时间
            time_t time() const;

            // 获取文件的大小
            long size() const;

            // 读取文件内容
            std::string read() const;

            // 写入文件
            bool write(const std::string &data);
        private:
            std::string m_path;
        };
    }
}

#endif //NETWORK_STUDY_FILE_H
//
// Created by aglorice on 2026/1/13.
//

#include "directory.h"

using namespace yazi::fs;

Directory::Directory() {
    m_path = ".";
}

Directory::Directory(const std::string &path):m_path(path) {

}

std::string Directory::path() const {

}


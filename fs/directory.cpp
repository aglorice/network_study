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
    return m_path;
}

char Directory::separator() {
#ifdef WIN32
    return '\\';
#else
    return '/';
#endif
}

bool Directory::is_absolute_path(const std::string &path) {
    if (path.empty()) {
        return false;
    }
    char sep = Directory::separator();
    std::string filepath = path;
#ifdef WIN32
    std::replace(filepath.begin(),filepath.end(),'/',sep);
#endif
}




//
// Created by aglorice on 2026/1/13.
//

#include "directory.h"

#include <sys/_types/_s_ifmt.h>

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

    std::vector<std::string> output = String::split(filepath,sep);

#ifdef WIN32
    if (output[0].find(':') != std::string::npos)
#else
    if (output[0].empty())
#endif
    {
        return true;
    }
    return false;
}

std::string Directory::normalize_path(const std::string &path) {
    char sep = separator();

    const std::string& filepath = path;
#ifdef WIN32
    std::replace(filepath.begin(),filepath.end(),'/',sep);
#endif
    std::vector<std::string> path_list;
    if (!is_absolute_path(path)) {
        char cmd[PATH_MAX] = {0};
        getcwd(cmd,PATH_MAX);
        path_list = String::split(cmd,sep);
    }
    for (const auto &dir : String::split(filepath,sep)) {
        if (dir.empty()) {
            continue;
        }
        if (dir == ".") {
            continue;
        }else if (dir == "..") {
            path_list.pop_back();
        }else {
            path_list.push_back(dir);
        }
    }
    std::string temp = String::join(path_list,sep);
    return adjust_path(temp);
}

std::string Directory::adjust_path(const std::string &path) {
    std::string result = path;
    char sep = separator();

#ifdef WIN32
    if (path[path.size() - 1] == ':') {
        result += sep;
    }
#else
    if (result[0] != sep) {
        result = std::string(1,sep) + result;
    }
#endif
    return result;
}

bool Directory::create() {
    char sep = separator();
    std::vector<std::string> arr = String::split(m_path,sep);

    std::string path;
    for (const auto &dir :arr) {
        if (dir.empty()) {
            continue;
        }
        if (path.empty()) {
            path += dir;
        }else {
            path += sep + dir;
        }
        path = adjust_path(path);
        Directory temp(path);
        if (temp.exists()) {
            continue;
        }
        if (mkdir(path.c_str(), 0755) != 0) {
            return false;
        }

    }
    return true;
}


bool Directory::exists() const {
    if (m_path.empty()) {
        return false;
    }
    struct stat info = {0};
    if (stat(m_path.c_str(),&info) != 0) {
        return false;
    }
    if (info.st_mode & S_IFDIR) {
        return true;
    }
    return false;
}


bool Directory::remove() const {
    DIR *dir = opendir(m_path.c_str());
    if (dir == nullptr) {
        return false;
    }
    struct dirent *entry;
    while ((entry = readdir(dir))!= nullptr) {
        std::string filename = entry->d_name;
        if (filename == "." || filename == "..") {
            continue;
        }
        std::string fullname = m_path + separator() + filename;
        struct stat info = {0};
        if (stat(fullname.c_str(),&info) != 0) {
            std::cerr << "stat file error :" << fullname << std::endl;
            return false;
        }

        if (S_ISDIR(info.st_mode)) {
            Directory tmp(fullname);
            tmp.remove();
        }else {
            unlink(fullname.c_str());
        }
    }
    return true;
}


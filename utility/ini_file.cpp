//
// Created by aglorice on 2025/12/17.
//

#include "ini_file.h"

using namespace yazi::utility;

IniFile::IniFile(const std::string &filename) {
    load(filename);
}

std::string IniFile::trim( std::string s)  {
    std::string temp = " \r\n";
    if (s.empty()) {
        return s;
    }
    s.erase(0,s.find_first_not_of(temp));
    s.erase(s.find_last_not_of(temp)+1);
    return s;
}


bool IniFile::load(const std::string &filename) {
    m_sections.clear();
    m_filename = filename;

    std::ifstream ifs(filename);
    if (ifs.fail()) {
        throw std::logic_error("loading ini file failed； " + filename);
    }
    std::string name;
    std::string line;
    while (std::getline(ifs,line)) {
        line = trim(line);
        if (line.empty()) {
            continue;
        }
        if (line[0] == '#' || line[0] == ';') {
            continue;
        }
        if (line[0] == '[') {
            auto pos = line.find_first_of(']');
            if (pos == std::string::npos) {
                throw std::logic_error("invalid section : " + line);
            }
            name = trim(line.substr(1,pos-1));
            m_sections[name] = Section();
        }
        // 这里就是解析 key = value
        else {
            auto pos = line.find('=');
            if (pos == std::string::npos) {
                throw std::logic_error("invalid option : " + line);
            }
            std::string key = trim(line.substr(0,pos));
            Value value = trim(line.substr(pos+1));
            m_sections[name][key] = value;
        }
    }
    ifs.close(); // 关闭文件
    return true;
}


std::string IniFile::str() const {
    std::stringstream ss;
    for (const auto &[fst, snd] : m_sections) {
        ss << "[" << fst << "]" << std::endl;
        for (const auto &[key, value] : snd) {
            ss << key << " = " << static_cast<std::string>(value) << std::endl;
        }
    }
    ss << std::endl;
    return ss.str();
}


void IniFile::show() const {
    std::cout << str();
}

Value &IniFile::get(const std::string &section, const std::string &key) {
    return m_sections[section][key];
}

void IniFile::set(const std::string &section, const std::string &key, const Value &val) {
    m_sections[section][key] = val;
}


bool IniFile::has(const std::string &section) {
    return m_sections.find(section) != m_sections.end();
}

bool IniFile::has(const std::string &section, const std::string &key) {
    auto it = m_sections.find(section);
    if (it == m_sections.end()) {
        return false;
    }
    return it->second.find(key) != it->second.end();
}

void IniFile::remove(const std::string &section) {
    m_sections.erase(section);
}

void IniFile::remove(const std::string &section, const std::string &key) {
    auto it = m_sections.find(section);
    if (it == m_sections.end()) {
        return;
    }
    m_sections[section].erase(key);
}

void IniFile::clear() {
    m_sections.clear();
}

void IniFile::save(const std::string &filename) {
    std::ofstream ofs(filename);
    if (ofs.fail()) {
        throw std::logic_error("saving ini file failed : " + filename);
    }
    ofs << str();
    ofs.close();
}





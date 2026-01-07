//
// Created by aglorice on 2026/1/2.
//

#include "xml.h"
#include "parser.h"

using namespace yazi::xml;

Xml::Xml(const char *name) : m_name(name) {

}

Xml::Xml(const std::string &name) : m_name(name) {

}

std::string Xml::name() const {
    return m_name;
}

void Xml::name(const std::string &name) {
    m_name = name;
}

std::string Xml::text() const {
    return m_text;
}

void Xml::text(const std::string &text) {
    m_text = text;
}


Value &Xml::attr(const std::string &key) {
    return m_attrs[key];
}

void Xml::attr(const std::string &key, const Value &value) {
    m_attrs[key] = value;
}


void Xml::append(const Xml &child) {
    m_child.push_back(child);
}

void Xml::remove(int index) {
    if (m_child.empty()) {
        return;
    }
    int size = (int)m_child.size();
    if (index <0 || index >= size) {
        return;
    }
    m_child.erase(m_child.begin()+index);
}

void Xml::remove(const char *name) {
    for (auto it = m_child.begin();it!=m_child.end();) {
        if (it->name() == name) {
            it = m_child.erase(it);
        }else {
            ++it;
        }
    }
}

void Xml::remove(const std::string &name) {
    remove(name.c_str());
}


Xml &Xml::operator[](const char *name) {
    for (auto it = m_child.begin();it!=m_child.end();++it) {
        if (it->name() == name) {
            return *it;
        }
    }
    m_child.emplace_back(name);
    return m_child.back();
}

Xml &Xml::operator[](const std::string &name) {
    return (*this)[name.c_str()];
}

Xml &Xml::operator[](int index) {
    return m_child.at(index);
}


int Xml::size() const {
    return static_cast<int>(m_child.size());
}

bool Xml::empty() const {
    return m_child.empty();
}

void Xml::clear()  {
    m_name.clear();
    m_attrs.clear();
    m_child.clear();
    m_attrs.clear();
}


Xml::~Xml() {
    clear();
}


std::string Xml::str() const {
    if (m_name.empty()) {
        return "";
    }
    std::ostringstream oss;
    oss << "<";
    oss << m_name;
    for (auto it = m_attrs.begin();it!=m_attrs.end();++it) {
        oss << " " << it->first << "=" << "\"" << it->second << "\"";
    }
    oss << ">";
    for (auto it = m_child.begin();it != m_child.end();++it) {
        oss << it->str();
    }
    oss << m_text;
    oss << "</" << m_name << ">";
    return oss.str();
}

void Xml::copy(const Xml &xml) {
    clear();
    m_name = xml.m_name;
    m_text = xml.m_text;
    m_attrs = xml.m_attrs;
    m_child = xml.m_child;
}

Xml::Xml(const Xml &other) {
    copy(other);
}

Xml &Xml::operator=(const Xml &other) {
    if (this == &other) {
        return *this;
    }
    copy(other);
    return *this;
}

bool Xml::save(const std::string &filename) const {
    std::ofstream ofs(filename);
    if (ofs.fail()) {
        return false;
    }
    ofs << str();
    ofs.close();
    return true;
}

void Xml::swap(Xml &other) {
    clear();
    m_name.swap(other.m_name);
    m_text.swap(other.m_text);
    m_attrs.swap(other.m_attrs);
    m_child.swap(other.m_child);
}

Xml::Xml(Xml &&other) {
    swap(other);
}

Xml &Xml::operator=(Xml &&other) {
    if (this == &other) {
        return *this;
    }
    swap(other);
    return *this;
}

void Xml::append(Xml &&child) {
    m_child.push_back(std::move(child));
}

bool Xml::load(const std::string &filename) {
    Parser p;
    if (!p.load(filename)) {
        return false;
    }
    *this = p.parse();
    return true;
}

bool Xml::load(const char *buff, int len) {
    Parser p;
    if (!p.load(buff,len)) {
        return false;
    }
    *this = p.parse();
    return true;
}









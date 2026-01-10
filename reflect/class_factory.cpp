//
// Created by aglorice on 2026/1/7.
//

#include "class_factory.h"

using namespace yazi::reflect;

const std::string &Object::get_class_name() const {
    return m_class_name;
}

void Object::set_class_name(const std::string &class_name) {
    m_class_name = class_name;
}

void ClassFactory::register_class(const std::string &class_name, create_object func) {
    m_class_map[class_name] = func;
}

Object *ClassFactory::create_class(const std::string &class_name) {
    auto it = m_class_map.find(class_name);
    if (it == m_class_map.end()) {
        return nullptr;
    }
    return it->second();
}

void ClassFactory::register_class_field(const std::string &class_name, const std::string &field_name, const std::string &field_type, size_t offset) {
    m_class_field[class_name].push_back(new ClassField(field_name,field_type,offset));
}

int ClassFactory::get_class_field_count(const std::string &class_name) {
    return (int)m_class_field[class_name].size();
}

ClassField *ClassFactory::get_class_field(const std::string &class_name, int pos) {
    int size = m_class_field[class_name].size();
    if (pos < 0 || pos >= size) {
        return nullptr;
    }
    return m_class_field[class_name][pos];
}

ClassField *ClassFactory::get_class_field(const std::string &class_name, const std::string &field_name) {
    auto &fields = m_class_field[class_name];
    for (auto it = fields.begin();it!=fields.end();++it) {
        if ((*it)->name() == field_name) {
            return *it;
        }
    }
    return nullptr;
}

ClassField *Object::get_field(const std::string &field_name) {
    return Singleton<ClassFactory>::instance()->get_class_field(m_class_name,field_name);
}

ClassField *Object::get_field(int pos) {
    return Singleton<ClassFactory>::instance()->get_class_field(m_class_name,pos);
}

int Object::get_field_count() {
    return Singleton<ClassFactory>::instance()->get_class_field_count(m_class_name);
}

void ClassFactory::register_class_method(const std::string &class_name, const std::string &method_name, uintptr_t method) {
    m_class_method[class_name].push_back(new ClassMethod(method_name,method));
}

int ClassFactory::get_class_method_count(const std::string &class_name) {
    return m_class_method[class_name].size();
}


ClassMethod *ClassFactory::get_class_method(const std::string &class_name, int pos) {
    int size = (int)m_class_method[class_name].size();
    if (pos < 0 || pos > size) {
        return nullptr;
    }
    return m_class_method[class_name][pos];
}

ClassMethod *ClassFactory::get_class_method(const std::string &class_name, const std::string &method_name) {
    auto &methods = m_class_method[class_name];
    for (auto it = methods.begin();it != methods.end();++it) {
        if ((*(it))->name() == method_name) {
            return *it;
        }
    }
    return nullptr;
}






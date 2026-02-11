//
// Created by aglorice on 2026/2/11.
//

#include "module.h"

using namespace yazi::py;

void Module::import(const std::string &name) {
    PyObject *module = PyImport_ImportModule(name.c_str());
    if (module == nullptr) {
        throw std::logic_error("module not found: " + name);
    }
    m_module = module;
}

void Module::import(const char * name) {
    PyObject * module = PyImport_ImportModule(name);
    if (module == nullptr) {
        throw std::logic_error("module not found: " + std::string(name));
    }
    m_module = module;
}

Module::Module(const std::string &name) {
    import(name);
}


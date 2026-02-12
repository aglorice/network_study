//
// Created by aglorice on 2026/2/11.
//

#include "function.h"

using namespace yazi::py;

void Function::call() {
    PyObject_CallObject(m_func,nullptr);
}

Function::Function(const Module &module, const std::string &name){
    PyObject * func = PyObject_GetAttrString(module.m_module,name.c_str());
    if (func == nullptr) {
        throw std::logic_error("function not found: " + name);
    }
    if (!PyCallable_Check(func)) {
        throw std::logic_error("object not callable" + name);
    }
    m_func = func;
}

Function::Function(const Object &obj, const std::string &name) {
    PyObject * func = PyObject_GetAttrString(obj.m_object,name.c_str());
    if (func == nullptr) {
        throw std::logic_error("function not found: " + name);
    }
    if (!PyCallable_Check(func)) {
        throw std::logic_error("object not callable" + name);
    }
    m_func = func;
}

//
// Created by aglorice on 2026/2/12.
//

#include "class.h"

using namespace yazi::py;

Class::Class(const Module &module, const std::string &name) {
    PyObject * cls = PyObject_GetAttrString(module.m_module,name.c_str());
    if (cls == nullptr) {
        throw std::logic_error("class not found: " + name);
    }
    m_class = cls;
}

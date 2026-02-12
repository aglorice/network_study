//
// Created by aglorice on 2026/2/12.
//

#include "object.h"

using namespace yazi::py;

Object::Object(const Class &cls) : m_object(nullptr) {
    m_object = PyObject_CallObject(cls.m_class,nullptr);
}



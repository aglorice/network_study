//
// Created by aglorice on 2026/2/12.
//

#ifndef NETWORK_STUDY_OBJECT_H
#define NETWORK_STUDY_OBJECT_H
#include <Python.h>
#include "argument.h"
#include "class.h"

namespace yazi {
    namespace py {
        class Object {
            friend class Function;
        public:
            Object() = default;
            Object(const Class & cls);

            template<typename ...Args>
            Object(const Class & cls,Args... args);

            ~Object() = default;
        private:
            PyObject * m_object;
        };

        template<typename... Args>
        Object::Object(const Class &cls, Args... args) {
            Argument arg;
            arg.bind(args...);
            m_object = PyObject_CallObject(cls.m_class,arg.m_args);
        }

    }
}
#endif //NETWORK_STUDY_OBJECT_H
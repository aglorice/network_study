//
// Created by aglorice on 2026/2/12.
//

#ifndef NETWORK_STUDY_CLASS_H
#define NETWORK_STUDY_CLASS_H
#include "module.h"

namespace yazi {
    namespace py {
        class Class {
            friend class Object;
        public:
            Class() = default;
            ~Class() = default;

            Class(const Module &module,const std::string &name);
        private:
            PyObject * m_class = nullptr;
        };
    }
}

#endif //NETWORK_STUDY_CLASS_H
//
// Created by aglorice on 2026/2/11.
//

#ifndef NETWORK_STUDY_MODULE_H
#define NETWORK_STUDY_MODULE_H
#include <Python.h>
#include <stdexcept>
#include <string>

namespace yazi {
    namespace py {
        class Module {
            friend class Function;
        public:
            Module() = default;
            Module(const std::string &name);
            ~Module() = default;

            void import(const std::string &name);
            void import(const char * name);

        private:
            PyObject * m_module = nullptr;
        };
    }
}


#endif //NETWORK_STUDY_MODULE_H
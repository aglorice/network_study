//
// Created by aglorice on 2026/2/11.
//

#ifndef NETWORK_STUDY_FUNCTION_H
#define NETWORK_STUDY_FUNCTION_H
#include <string>
#include "module.h"
namespace yazi {
    namespace py {
        class Function {
        public:
            Function() = default;
            Function(const Module &module,const std::string &name);
            ~Function() = default;
            void call();
        private:
            PyObject * m_func = nullptr;
        };
    }
}
#endif //NETWORK_STUDY_FUNCTION_H
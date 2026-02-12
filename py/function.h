//
// Created by aglorice on 2026/2/11.
//

#ifndef NETWORK_STUDY_FUNCTION_H
#define NETWORK_STUDY_FUNCTION_H
#include <string>
#include "module.h"
#include "argument.h"
namespace yazi {
    namespace py {
        class Function {
        public:
            Function() = default;
            Function(const Module &module,const std::string &name);
            ~Function() = default;

            void call();

            template<typename R>
            R call();

            template<typename R,typename ...Args>
            R call(Args... args);
        private:
            PyObject * m_func = nullptr;
        };

        template<typename R>
        R Function::call() {
            PyObject *ret = PyObject_CallObject(m_func,nullptr);
            Argument arg;
            return arg.parse_result<R>(ret);
        }

        template<typename R, typename... Args>
        R Function::call(Args... args) {
            Argument arg;
            arg.bind(args...);
            PyObject *ret = PyObject_CallObject(m_func,arg.m_args);
            return arg.parse_result<R>(ret);
        }
    }
}
#endif //NETWORK_STUDY_FUNCTION_H
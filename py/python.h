//
// Created by aglorice on 2026/2/11.
//

#ifndef NETWORK_STUDY_PYTHON_H
#define NETWORK_STUDY_PYTHON_H
#include <Python.h>
#include <string>
#include <stdexcept>

#include "module.h"
#include "function.h"
#include "object.h"
#include "class.h"
#include "argument.h"
namespace yazi {
    namespace py {
        class Python {
        public:
            Python();
            ~Python();

            void run(const std::string &str);
            void run(const char * str);
        };
    }
}


#endif //NETWORK_STUDY_PYTHON_H
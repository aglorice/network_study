//
// Created by aglorice on 2026/2/11.
//

#include "python.h"

using namespace yazi::py;

Python::Python() {
    Py_Initialize();
    if (!Py_IsInitialized()) {
        throw std::logic_error("Python init failed");
    }
}

Python::~Python() {
    // 结束调用，释放资源
    Py_Finalize();
}

void Python::run(const std::string &str) {
    run(str.c_str());
}

void Python::run(const char *str) {
    PyRun_SimpleString(str);
}



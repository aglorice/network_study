#include <Python.h>
#include <iostream>


int main() {
    Py_Initialize();
    if (!Py_IsInitialized()) {
        std::cout << "python init failed " << std::endl;
        return -1;
    }
    // 导入系统的 sys 模块
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append('./../script')");

    // 导入用户自定义的模块
    PyObject * module = PyImport_ImportModule("test1");
    if (module == nullptr) {
        std::cout << "module not found :test1.py" << std::endl;
        return -1;
    }
    PyObject * func = PyObject_GetAttrString(module,"say");
    if (func == nullptr) {
        std::cout << "function not found: say" << std::endl;
        return -1;
    }
    if (!PyCallable_Check(func)) {
        std::cout << "function not callable" << std::endl;
        return -1;
    }
    // 调用函数
    PyObject_CallObject(func,nullptr);
    // 结束调用，释放资源
    Py_Finalize();
    return 0;
}

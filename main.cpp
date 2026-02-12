#include "py/python.h"

#include <iostream>

using namespace yazi::py;

int main() {
    auto py = Python();
    py.run("import sys");
    py.run("sys.path.append('./../script')");
    try {
        auto module = Module("test3");
        Class cls(module,"Person");
        Object object(cls,"jack",20);
        auto func = Function(object,"foo");
        func.call();
    }catch (std::exception & e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
    return 0;
}

// #include <Python.h>
// #include <iostream>
//
//
// int main() {
//     Py_Initialize();
//     if (!Py_IsInitialized()) {
//         std::cout << "python init failed " << std::endl;
//         return -1;
//     }
//     // 导入系统的 sys 模块
//     PyRun_SimpleString("import sys");
//     PyRun_SimpleString("sys.path.append('./../script')");
//
//     // 导入用户自定义的模块
//     PyObject * module = PyImport_ImportModule("test3");
//     if (module == nullptr) {
//         std::cout << "module not found :test1.py" << std::endl;
//         return -1;
//     }
//     PyObject * cls = PyObject_GetAttrString(module,"Person");
//     if (cls == nullptr) {
//         std::cout << "class not found: say" << std::endl;
//         return -1;
//     }
//     if (!PyCallable_Check(cls)) {
//         std::cout << "class not callable" << std::endl;
//         return -1;
//     }
//     // 构造函数参数
//     PyObject *args = PyTuple_New(2);
//
//     PyTuple_SetItem(args,0,Py_BuildValue("s","aglorice"));
//     PyTuple_SetItem(args,1,Py_BuildValue("i",21));
//     // 接受函数的返回值
//     PyObject * ret = PyObject_CallObject(cls,args);
//
//     // 获取成员函数
//     PyObject * func = PyObject_GetAttrString(ret,"foo");
//     if (func == nullptr) {
//         std::cout << "function not found: foo" <<std::endl;
//         return 1;
//     }
//
//     if (!PyCallable_Check(func)) {
//         std::cout << "not a callable object" << std::endl;
//         return 1;
//     }
//     PyObject_CallObject(func,nullptr);
//
//     // 结束调用，释放资源
//     Py_Finalize();
//     return 0;
// }

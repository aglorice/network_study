#include "timer/timer_manager.h"
#include <iostream>
#include <string>

using namespace yazi::timer;

void foo() {
    std::cout << "foo" << std::endl;
}

void bar(const std::string & name) {
    std::cout << "bar : " << name << std::endl;
}
int main() {

    auto mgr = yazi::utility::Singleton<TimerManager>::instance();
    mgr->schedule(1000,foo);

    mgr->schedule(1500,bar,"aglorice");
    while (true) {
        mgr->update();
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

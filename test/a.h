//
// Created by aglorice on 2025/12/18.
//

#ifndef NETWORK_STUDY_A_H
#define NETWORK_STUDY_A_H
#include <iostream>

#include "../reflect/class_register.h"

using namespace yazi::reflect;


class A : public Object {
public:
    A():m_name("A"),m_age(18) {
    }
    ~A() {}

    void f1() {
        std::cout << "f1" << std::endl;
    }

    int f2(const std::string name,int age) {
        std::cout << name << "-" << age << std::endl;
        return 0;
    }
public:
    std::string m_name;
    int m_age;
};

REGISTER_CLASS(A);
REGISTER_CLASS_FIELD(A,m_name,std::string);
REGISTER_CLASS_FIELD(A,m_age,int);
REGISTER_CLASS_METHOD(A,f1,void);
REGISTER_CLASS_METHOD(A,f2,int,const std::string &,int);
#endif //NETWORK_STUDY_A_H
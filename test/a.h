//
// Created by aglorice on 2025/12/18.
//

#ifndef NETWORK_STUDY_A_H
#define NETWORK_STUDY_A_H
#include <iostream>

#include "../utility/singleton.h"

using namespace yazi::utility;


class A {
    SINGLETON(A);
public:
    void show() {
        std::cout << "A" << std::endl;
    }
};


#endif //NETWORK_STUDY_A_H
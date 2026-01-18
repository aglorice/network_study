#include "fs/directory.h"
#include <iostream>
using namespace yazi::fs;


int main(int argc,char *argv[]) {
   Directory dir("/Users/aglorice/Downloads");
   std::cout << dir.size() << std::endl;


   return 0;
}
#include "fs/file.h"
#include <iostream>
using namespace yazi::fs;




int main(int argc,char *argv[]) {
   File file("./../main.log");
   std::cout << file.size() << std::endl;
   return 0;
}
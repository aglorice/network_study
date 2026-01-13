#include "fs/directory.h"
#include <iostream>
using namespace yazi::fs;




int main(int argc,char *argv[]) {
   Directory dir("/root/xxx/./../main.log");
   std::cout << dir.path() << std::endl;
   return 0;
}
#include "fs/directory.h"
#include <iostream>
using namespace yazi::fs;


int main(int argc,char *argv[]) {
   Directory dir("/Users/aglorice/Downloads/asd/c/c/c/c");
   std::cout << dir.is_absolute_path(dir.path()) << std::endl;
   std::cout << dir.normalize_path(dir.path()) << std::endl;
   std::cout << dir.remove();

   return 0;
}
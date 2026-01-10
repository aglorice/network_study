#include <functional>
#include "reflect/class_factory.h"
#include "test/a.h"

using namespace yazi::reflect;

class Test {
public:
   Test() = default;
   ~Test() = default;
   void foo() {
      std::cout << "Test::foo" << std::endl;
   }
};

typedef std::function<void(Test*)> test_method;




int main(int argc,char *argv[]) {
   auto factory = Singleton<ClassFactory>::instance();
   Object *a = factory->create_class("A");
   a->call("f1");
   int age = 19;
   std::string name = "askjdn";
   a->call("f2",std::move(name),std::move(age));


   return 0;
}
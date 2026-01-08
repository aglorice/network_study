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

   std::string name;
   int age;

   a->set<std::string>("m_name","aglorice");
   a->set<int>("m_age",17);
   a->get<std::string>("m_name",name);
   a->get<int>("m_age",age);
   std::cout << age << std::endl;
   std::cout << name << std::endl;

   test_method method = &Test::foo;

   Test t;
   // method(&t);
   // 这里是将指向成员函数的指针的类型改成uintptr_t，再由后面转会原来的类型在解引用调用该函数
   uintptr_t ptr = (uintptr_t)&method;
   (*(test_method*)(ptr))(&t);
   return 0;
}
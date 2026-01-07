#include <iostream>
#include "serialize/data_stream.h"

using namespace yazi::serialize;

class A : public Serializable {
public:
   A() = default;
   A(std::string name,int age): m_age(age),m_name(name) {
   }
   ~A() = default;
   SERIALIZE(m_name,m_age)

   void show() const {
      std::cout << "name = " << m_name << ", age = " << m_age;
   }
private:
   std::string m_name;
   int m_age;
};



int main(int argc,char *argv[]) {

   DataStream ds;
   A a2;
   ds.load("./../a.out");
   ds >> a2;
   a2.show();

   return 0;
}
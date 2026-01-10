//
// Created by aglorice on 2026/1/9.
//

#ifndef NETWORK_STUDY_CLASS_METHOD_H
#define NETWORK_STUDY_CLASS_METHOD_H
#include <string>
namespace yazi {
    namespace reflect {
        class ClassMethod {
        public:
            ClassMethod() : m_method(0) {}
            ClassMethod(const std::string &name,uintptr_t method) :m_name(name), m_method(method) {}
            ~ClassMethod() = default;

            [[nodiscard]] const std::string &name() const{return m_name;}
            [[nodiscard]] uintptr_t method() const{return m_method;}
        private:
            std::string m_name;
            uintptr_t m_method;
        };
    }
}

#endif //NETWORK_STUDY_CLASS_METHOD_H
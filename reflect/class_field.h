//
// Created by aglorice on 2026/1/8.
//

#ifndef NETWORK_STUDY_CLASS_FIELD_H
#define NETWORK_STUDY_CLASS_FIELD_H
#include <string>

namespace yazi {
    namespace reflect {
        class ClassField {
        public:
            ClassField() : m_offset(0){}
            ClassField(const std::string &name,const std::string &type,size_t offset): m_name(name),m_offset(offset),m_type(type){}
            ~ClassField() = default;

            [[nodiscard]] const std::string &name() const {return m_name;}
            [[nodiscard]] const std::string &type() const{return m_type;}
            size_t offset() const {return m_offset;}
        private:
            std::string m_name;
            std::string m_type;
            size_t m_offset; // 相当于在某个内的偏移量
        };
    }
}

#endif //NETWORK_STUDY_CLASS_FIELD_H
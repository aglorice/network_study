//
// Created by aglorice on 2026/1/7.
//

#ifndef NETWORK_STUDY_CLASS_FACTORY_H
#define NETWORK_STUDY_CLASS_FACTORY_H
#include <string>
#include <map>
#include "../utility/singleton.h"
#include "class_field.h"

using namespace yazi::utility;

namespace yazi {
    namespace reflect {
        class Object {
        public:
            Object() = default;
            virtual ~Object() = default;
            void set_class_name(const std::string& class_name);
            [[nodiscard]] const std::string & get_class_name() const;

            int get_field_count();
            ClassField * get_field(int pos);
            ClassField * get_field(const std::string & field_name);

            template <typename T>
            void get(const std::string&field_name,T &value);

            template<typename  T>
            void set(const std::string &field_name,const T &value);
        private:
            std::string m_class_name;
        };

        // 函数指针
        typedef Object *(*create_object)();
        class ClassFactory {
            SINGLETON(ClassFactory);
        public:
            // reflect class
            void register_class(const std::string &class_name,create_object func);
            Object * create_class(const std::string &class_name);

            // reflect class field
            void register_class_field(const std::string & class_name,const std::string & field_name,const std::string &field_type,size_t offset);
            int get_class_field_count(const std::string &class_name);
            ClassField * get_class_field(const std::string &class_name,int pos);
            ClassField * get_class_field(const std::string &class_name,const std::string & field_name);
        private:
            std::map<std::string,create_object> m_class_map;
            std::map<std::string,std::vector<ClassField*>> m_class_field;
        };

        template<typename T>
        void Object::get(const std::string &field_name, T &value) {
            ClassField *field = Singleton<ClassFactory>::instance()->get_class_field(m_class_name,field_name);
            if (field == nullptr) {
                return;
            }
            size_t offset = field->offset();
            value = *((T*)((unsigned char *)(this) + offset));
        }

        template<typename T>
        void Object::set(const std::string &field_name, const T &value) {
            ClassField *field = Singleton<ClassFactory>::instance()->get_class_field(m_class_name,field_name);
            if (field == nullptr) {
                return;
            }
            size_t offset = field->offset();
            *((T*)((unsigned char *)(this) + offset)) = value;
        }


    }
}

#endif //NETWORK_STUDY_CLASS_FACTORY_H
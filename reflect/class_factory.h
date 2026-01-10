//
// Created by aglorice on 2026/1/7.
//

#ifndef NETWORK_STUDY_CLASS_FACTORY_H
#define NETWORK_STUDY_CLASS_FACTORY_H
#include <string>
#include <map>
#include <functional>
#include "../utility/singleton.h"
#include "class_field.h"
#include "class_method.h"

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

            template<typename R = void,typename ...Args>
            R call(const std::string &method_name,Args&&... args);
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

            // register class method
            void register_class_method(const std::string &clas_name,const std::string &method_name, uintptr_t method);
            int get_class_method_count(const std::string &class_name);
            ClassMethod *get_class_method(const std::string &class_name,int pos);
            ClassMethod* get_class_method(const std::string&class_name,const std::string &method_name);
        private:
            std::map<std::string,create_object> m_class_map;
            std::map<std::string,std::vector<ClassField*>> m_class_field;
            std::map<std::string,std::vector<ClassMethod*>> m_class_method;
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

        template<typename R, typename... Args>
        R Object::call(const std::string &method_name, Args &&... args) {
            ClassFactory* factory = Singleton<ClassFactory>::instance();
            ClassMethod * method = factory->get_class_method(m_class_name,method_name);
            if (method == nullptr) {
                return R();
            }
            auto func = method->method();
            typedef std::function<R(decltype(this),Args...args)> class_method;
            return (*((class_method*)func))(this,args...);
        }



    }
}

#endif //NETWORK_STUDY_CLASS_FACTORY_H
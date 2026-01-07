//
// Created by aglorice on 2025/12/29.
//

#ifndef NETWORK_STUDY_JSON_H
#define NETWORK_STUDY_JSON_H
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <ostream>
#include <stdexcept>
#include <iostream>


namespace yazi {
    namespace json {
        class Json {
        public:
            enum Type {
                JSON_NULL = 0,
                JSON_BOOL,
                JSON_INT,
                JSON_DOUBLE,
                JSON_STRING,
                JSON_ARRAY,
                JSON_OBJET,
            };
            Json();
            Json(Type type);
            Json(bool value);
            Json(int value);
            Json(double value);
            Json(const char * value);
            Json(const std::string & value);

            Json(const Json & ohter);
            Json(Json&& other) noexcept ;

            void clear();

            Json& operator = (bool value);
            Json& operator = (int value);
            Json& operator = (double value);
            Json& operator = (const char * value);
            Json& operator = (const std::string  &value);
            Json& operator=(const Json & other);
            Json& operator = (Json &&other) noexcept;

            Type type() const;
            bool is_null() const;
            bool is_bool() const;
            bool is_int() const;
            bool is_double() const;
            bool is_string() const;
            bool is_array() const;
            bool is_object() const;

            [[nodiscard]] bool as_bool() const;
            [[nodiscard]] int as_int() const;
            [[nodiscard]] double as_double() const;
            [[nodiscard]] std::string as_string() const;


            void append(const Json &value);
            void append( Json &&value);
            bool has(int index);
            bool has(const char * key) const;
            bool has(const std::string & key) const;

            Json get(const char * key);
            Json get(const std::string &key);

            void remove(const char * key);
            void remove(const std::string &key);

            Json& operator [](const char *key);
            Json& operator [](const std::string & key);

            Json get(int index);
            void remove(int index);
            Json & operator [] (int index);

            int size() const;
            bool empty() const;

            ~Json();

            [[nodiscard]] std::string str() const;

            operator bool();
            operator bool() const;

            operator int();
            operator int() const;

            operator double();
            operator double() const;

            operator std::string();
            operator std::string() const;



            friend std::ostream & operator << (std::ostream & os,const Json &json) {
                os << json.str();
                return os;
            }

            // 遍历数组
            typedef std::vector<Json>::iterator iterator;
            iterator begin() {
                return (m_value.m_array)->begin();
            }
            iterator end() {
                return (m_value.m_array)->end();
            }

            void parse(const std::string &file);
            void parse(const char * buf,int len);
        private:
            void copy(const Json & other);
            void swap(Json &other);
        private:
            union Value {
                bool m_bool;
                int m_int;
                double m_double;
                std::string * m_string;
                std::vector<Json> * m_array;
                std::map<std::string,Json> *m_object;
            };

            Type m_type;
            Value m_value;
        };
    }
}

#endif //NETWORK_STUDY_JSON_H
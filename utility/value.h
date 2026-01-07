//
// Created by aglorice on 2025/12/17.
//

#ifndef NETWORK_STUDY_VALUE_H
#define NETWORK_STUDY_VALUE_H
#include <string>
#include <iostream>
#include <sstream>

namespace yazi {
    namespace utility {
        class Value {
        public:
            enum Type {
                V_NULL = 0,
                V_BOOL,
                V_INT,
                V_FLOAT,
                V_DOUBLE,
                V_STRING
            };

            Value();
            Value(bool value);
            Value(int value);
            Value(unsigned int value);
            Value(float value);
            Value(double value);
            Value(const char * value);
            Value(const std::string & value);
            ~Value() = default;

            Value & operator = (bool value);
            Value & operator = (int value);
            Value & operator = (unsigned int value);
            Value & operator = (float value);
            Value & operator = (double value);
            Value & operator = (const char * value);
            Value & operator = (const std::string& value);
            Value & operator = (const Value &other) = default;

            [[nodiscard]] Type type() const;

            [[nodiscard]] bool is_null() const;
            [[nodiscard]] bool is_bool() const;
            [[nodiscard]] bool is_int() const;
            [[nodiscard]] bool is_float() const;
            [[nodiscard]] bool is_double() const;
            [[nodiscard]] bool is_string() const;

            bool operator==(const Value & other) const;
            bool operator!=(const Value & other) const;

            operator bool();
            operator bool() const;

            operator int();
            operator int() const;

            operator unsigned int();
            operator unsigned int() const;

            operator float();
            operator float() const;

            operator double();
            operator double() const;

            operator std::string();
            operator std::string() const;

            void show() const;

            friend std::ostream & operator <<(std::ostream &os,const Value &value) {
                os << std::string(value);
                return os;
            }
        private:
            Type m_type;
            std::string m_value;
        };
    }
}

#endif //NETWORK_STUDY_VALUE_H
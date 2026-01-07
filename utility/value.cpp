//
// Created by aglorice on 2025/12/17.
//

#include "value.h"


using namespace yazi::utility;


Value::Value() : m_type(V_NULL) {

}

Value::Value(const bool value) : m_type(V_BOOL) {
    m_value = value ? "true" : "false";
}


Value::Value(const std::string &value) : m_type(V_STRING){
    m_value = value;
}

Value::Value(const char *value) : m_type(V_STRING) {
    m_value = value;
}

Value::Value(const double value) : m_type(V_DOUBLE){
    m_value = std::to_string(value);
}

Value::Value(const float value) : m_type(V_FLOAT){
    m_value = std::to_string(value);
}

Value::Value(const int value) : m_type(V_INT) {
    m_value = std::to_string(value);
}

Value::Value(const unsigned int value) : m_type(V_INT) {
    m_value = std::to_string(value);
}


void Value::show() const {
    std::string type;
    switch (m_type) {
        case V_NULL:
            type = "null";
            break;
        case V_BOOL:
            type = "bool";
            break;
        case V_INT:
            type = "int";
            break;
        case V_STRING:
            type = "string";
            break;
        case V_DOUBLE:
            type = "double";
            break;
        case V_FLOAT:
            type = "float";
            break;
        default:
            break;
    }
    std::cout << "type = " << type << ", value = " << m_value << std::endl;
}

Value &Value::operator=(const bool value) {
    m_type = V_BOOL;
    m_value = value ? "true" : "false";
    return *this;
}

Value &Value::operator=(const int value) {
    m_type = V_INT;
    m_value = std::to_string(value);
    return *this;
}


Value &Value::operator=(const float value) {
    m_type = V_FLOAT;
    m_value = std::to_string(value);
    return *this;
}


Value &Value::operator=(const char *value) {
    m_type = V_STRING;
    m_value = value;
    return *this;
}

Value &Value::operator=(const std::string &value) {
    m_type = V_STRING;
    m_value = value;
    return *this;
}

Value &Value::operator=(const double value) {
    m_type = V_DOUBLE;
    m_value = std::to_string(value);
    return *this;
}

Value &Value::operator=(const unsigned int value) {
    m_type = V_INT;
    m_value = std::to_string(value);
    return *this;
}


Value::Type Value::type() const {
    return m_type;
}

bool Value::is_bool() const {
    return m_type == V_BOOL;
}

bool Value::is_double() const {
    return m_type == V_DOUBLE;
}

bool Value::is_float() const {
    return m_type == V_FLOAT;
}

bool Value::is_int() const {
    return m_type == V_INT;
}

bool Value::is_null() const {
    return m_type == V_NULL;
}

bool Value::is_string() const {
    return m_type == V_STRING;
}


bool Value::operator==(const Value &other) const {
    return m_type == other.m_type && m_value == other.m_value;
}

bool Value::operator!=(const Value &other) const {
    return m_type != other.m_type || m_value != other.m_value;
}


Value::operator bool() const {
    return m_value == "true";
}

Value::operator double() const {
    double value = 0;
    std::stringstream ss;
    ss << m_value;
    ss >> value;
    return value;
}

Value::operator int() const {
    int value = 0;
    std::stringstream ss;
    ss << m_value;
    ss >> value;
    return value;
}

Value::operator float() const {
    float value = 0;
    std::stringstream ss;
    ss << m_value;
    ss >> value;
    return value;
}

Value::operator unsigned int() const {
    unsigned int value = 0;
    std::stringstream ss;
    ss << m_value;
    ss >> value;
    return value;
}

Value::operator std::string() const {
    return m_value;
}


Value::operator bool()  {
    return m_value == "true";
}

Value::operator double()  {
    double value = 0;
    std::stringstream ss;
    ss << m_value;
    ss >> value;
    return value;
}

Value::operator int() {
    int value = 0;
    std::stringstream ss;
    ss << m_value;
    ss >> value;
    return value;
}

Value::operator float() {
    float value = 0;
    std::stringstream ss;
    ss << m_value;
    ss >> value;
    return value;
}

Value::operator unsigned int() {
    unsigned int value = 0;
    std::stringstream ss;
    ss << m_value;
    ss >> value;
    return value;
}

Value::operator std::string() {
    return m_value;
}























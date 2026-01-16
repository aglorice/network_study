//
// Created by aglorice on 2025/12/20.
//
#include <sstream>

#include "string.h"

using namespace yazi::utility;

std::string String::to_lower(const std::string &input) {
    std::string str = input;
    std::transform(str.begin(),str.end(),str.begin(),tolower);
    return str;
}

std::string String::to_upper(const std::string &input) {
    std::string str = input;
    std::transform(str.begin(),str.end(),str.begin(),toupper);
    return str;
}

std::string String::ltrim(const std::string &input, const std::string &trims) {
    std::string str= input;
    size_t pos = str.find_first_not_of(trims);
    if (pos != std::string::npos) {
        str.erase(0,pos);
    }else {
        str.clear();
    }
    return str;
}

std::string String::rtrim(const std::string &input, const std::string &trims) {
    std::string str= input;
    size_t pos = str.find_last_not_of(trims);
    if (pos != std::string::npos) {
        str.erase(pos+1);
    }else {
        str.clear();
    }
    return str;
}


std::string String::trim(const std::string &input, const std::string &trims) {
    std::string str = ltrim(input,trims);
    return rtrim(str,trims);
}

std::vector<std::string> String::split(const std::string &input, const std::string &separator) {
    std::vector<std::string> ret;
    size_t last = 0;
    size_t index = input.find(separator,last);
    size_t separator_len = separator.length();

    while (index != std::string::npos) {
        std::string str =  input.substr(last,index-last);
        ret.push_back(str);
        last = index+separator_len;
        index = input.find(separator,last);
    }
    if (last< input.length()) {
        ret.push_back(input.substr(last));
    }
    return ret;
}

std::vector<std::string> String::split(const std::string &input, char separator) {
    std::string temp(1,separator);
    return split(input, temp);
}

std::string String::join(const std::vector<std::string> &input, const std::string &separator) {
    std::ostringstream oss;
    for (auto it = input.begin();it != input.end();++it) {
        if (it != input.begin()) {
            oss<< separator;
        }
        oss << *it;
    }
    return oss.str();
}

std::string String::join(const std::vector<std::string> &input, char separator) {
    std::string temp(1,separator);
    return join(input,temp);
}

bool String::has_suffix(const std::string &input, const std::string &suffix) {
    if (suffix.size() > input.size() ) {
        return false;
    }
    return input.substr(input.size()-suffix.size()) == suffix;
}

bool String::has_prefix(const std::string &input, const std::string &prefix) {
    if (prefix.size() > input.size() ) {
        return false;
    }
    return input.substr(0,prefix.size()) == prefix;
}

std::string String::capitalize(const std::string &input) {
    std::string str = input;
    if (str.empty()) {
        return input;
    }
    char ch = input[0];
    if (islower(ch)) {
        ch = toupper(ch);
        std::replace(str.begin(),str.begin()+1,str[0],ch);
    }
    return str;
}


std::string String::format(const char *format, ...) {
    std::string result;
    va_list arg_ptr;
    va_start(arg_ptr,format);
    int len = vsnprintf(nullptr,0,format,arg_ptr);
    va_end(arg_ptr);

    if (len > 0) {
        char *buf = new char[len + 1];
        va_start(arg_ptr,format);
        vsnprintf(buf,len+1,format,arg_ptr);
        va_end(arg_ptr);
        buf[len] = 0;
        result = buf;
        delete [] buf;
    }
    return result;
}








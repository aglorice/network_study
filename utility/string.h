//
// Created by aglorice on 2025/12/20.
//

#ifndef NETWORK_STUDY_STRING_H
#define NETWORK_STUDY_STRING_H
#include <string>
#include <algorithm>
#include <cctype>
#include <vector>
#include <sstream>
#include <cstdarg>

namespace yazi {
    namespace utility {
        class String {
        public:
            String() = default;
            ~String() = default;

            static std::string  to_lower(const std::string &input);
            static std::string  to_upper(const std::string &input);

            static std::string ltrim(const std::string &input,const std::string &trims);
            static std::string rtrim(const std::string &input,const std::string &trims);
            static std::string trim(const std::string &input,const std::string &trims);

            static std::vector<std::string> split(const std::string &input,const std::string &separator);
            static std::vector<std::string> split(const std::string &input,char separator);

            static std::string join(const std::vector<std::string> &input,const std::string & separator);
            static std::string join(const std::vector<std::string> &input,char  separator);

            static bool has_prefix(const std::string &input ,const std::string&prefix);
            static bool has_suffix(const std::string &input ,const std::string&suffix);

            static std::string capitalize(const std::string &input);
            static std::string format(const char *format,...);
        };
    }
}

#endif //NETWORK_STUDY_STRING_H
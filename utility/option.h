//
// Created by aglorice on 2025/12/17.
//

#ifndef NETWORK_STUDY_OPTION_H
#define NETWORK_STUDY_OPTION_H

#include <map>
#include <string>
#include <iostream>
#include <sstream>
#include "value.h"

namespace yazi {
    namespace utility {
        class Option {
        public:
            enum Type {
                OPT_UNKNOWN = 0,
                OPT_NO,
                OPT_REQUIRED,
                OPT_OPTIONAL
            };

            Option() = default;
            ~Option() = default;

            void add(const std::string &opt,Type type);
            Type type(const std::string &opt) const;

            void parse(int argc,char *argv[]);
            void show() const;

            bool has(const std::string &opt) const;

            Value get(const std::string & opt);
        private:
            std::map<std::string,Type> m_opts;
            std::map<std::string,std::string> m_args;
        };
    }
}


#endif //NETWORK_STUDY_OPTION_H
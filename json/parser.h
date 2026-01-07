//
// Created by aglorice on 2026/1/2.
//

#ifndef NETWORK_STUDY_PARSER_H
#define NETWORK_STUDY_PARSER_H
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "json.h"


namespace yazi {
    namespace json {
        class Parser {
        public:
            Parser() = default;
            ~Parser() = default;

            void load(const std::string &filename);
            void load(const char * buf,int len);

            Json parse();
        private:
            void skip_white_space();
            char get_next_token();
            bool in_range(int x,int lower,int upper);


            Json parse_null();
            Json parse_bool();
            Json parse_number();
            std::string parse_string();
            Json parse_array();
            Json parse_object();
        private:
            std::string m_str;
            size_t m_idx;
        };
    }
}

#endif //NETWORK_STUDY_PARSER_H
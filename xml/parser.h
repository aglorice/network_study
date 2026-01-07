//
// Created by aglorice on 2026/1/3.
//

#ifndef NETWORK_STUDY_PARSER_H
#define NETWORK_STUDY_PARSER_H
#include <string>
#include <stdexcept>
#include "xml.h"

namespace yazi {
    namespace xml {
        class Parser {
        public:
            Parser() = default;
            ~Parser() = default;

            bool load(const std::string &filename);
            bool load(const char *buf,int len);
            Xml parse();
        private:
            void skip_white_space();
            bool parse_declaration();
            bool parse_comment();
            Xml parse_element();
            std::string parse_element_name();
            std::string parse_element_text();
            std::string parse_element_attr_key();
            std::string parse_element_attr_value();

        private:
            std::string m_str;
            int m_index = 0;
        };
    }
}
#endif //NETWORK_STUDY_PARSER_H
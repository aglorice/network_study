//
// Created by aglorice on 2026/1/3.
//

#include "parser.h"

using namespace yazi::xml;

bool Parser::load(const char *buf, int len) {
    m_str.assign(buf,len);
    m_index = 0;
    return true;
}

bool Parser::load(const std::string &filename) {
    std::ifstream ifs(filename);
    if (ifs.fail()) {
        return false;
    }
    std::ostringstream oss;
    oss << ifs.rdbuf();
    m_str = oss.str();
    m_index = 0;
    return true;
}


void Parser::skip_white_space() {
    while (m_str[m_index] == ' ' || m_str[m_index] == '\t' || m_str[m_index] == '\n' || m_str[m_index] == '\r') {
        m_index++;
    }
}

Xml Parser::parse() {
    skip_white_space();
    if (m_str.compare(m_index,5,"<?xml") == 0) {
        if (!parse_declaration()) {
            throw std::logic_error("parse declaration error");
        }
    }
    skip_white_space();
    while (m_str.compare(m_index,5,"<!--")==0) {
        if (!parse_comment()) {
            throw std::logic_error("parse comment error");
        }
        skip_white_space();
    }
    // 解析元素
    if (m_str[m_index] == '<' && (isalnum(m_str[m_index+1]) || m_str[m_index+1] == '_')) {
        return parse_element();
    }
    throw std::logic_error("parse element error");
}



bool Parser::parse_declaration() {
    if (m_str.compare(m_index,5,"<?xml") != 0) {
        return false;
    }
    m_index += 5;
    size_t pos = m_str.find("?>",m_index);
    if (pos == std::string::npos) {
        return false;
    }
    m_index = (int)pos + 2;
    return true;
}

bool Parser::parse_comment() {
    if (m_str.compare(m_index,4,"<!--")!=0) {
        return false;
    }
    m_index+=4;
    size_t pos = m_str.find("-->",m_index);
    if (pos == std::string::npos) {
        return false;
    }
    m_index =(int)pos + 3;
    return true;
}

Xml Parser::parse_element() {
    Xml elem;
    m_index++;
    skip_white_space();
    const std::string &name = parse_element_name();
    elem.name(name);
    while (m_str[m_index] != '\0') {
        skip_white_space();
        if (m_str[m_index] == '/') {
            if (m_str[m_index + 1] == '>') {
                m_index += 2;
                break;
            }
            throw std::logic_error("parse empty element error");
        }else if (m_str[m_index] == '>') {

            m_index++;
            skip_white_space();
            std::string text = parse_element_text();
            if (!text.empty()) {
                elem.text(text);
            }
        }else if (m_str[m_index] == '<') {
            if (m_str[m_index + 1] == '/') {
                std::string end_tag = "</" + name + ">";
                size_t pos = m_str.find(end_tag,m_index);
                if (pos == std::string::npos) {
                    throw std::logic_error("parse end tag error : "+name);
                }
                m_index = (int)pos + end_tag.size();
                break;
            }else if (m_str.compare(m_index,4,"<!--") == 0) {
                if (!parse_comment()) {
                    throw std::logic_error("parse comment error");
                }
            }else {
                elem.append(parse_element());
            }
        }else {
            // 解释xml的属性
            std::string key = parse_element_attr_key();
            skip_white_space();
            if (m_str[m_index] != '=') {
                throw std::logic_error("parse xml attr error : "+key);
            }
            m_index++;
            std::string value = parse_element_attr_value();
            elem.attr(key,value);
        }
    }
    return elem;
}


std::string Parser::parse_element_name() {
    int pos = m_index;
    if (isalnum(m_str[m_index]) || m_str[m_index] == '_') {
        m_index++;
        while (isalnum(m_str[m_index]) || m_str[m_index] == '_'|| m_str[m_index] == '-' || m_str[m_index] == ':' || m_str[m_index] == '.') {
            m_index++;
        }
    }
    return m_str.substr(pos,m_index-pos);
}

std::string Parser::parse_element_text() {

    int pos = m_index;
    while (m_str[m_index] != '<') {
        m_index++;
    }
    return m_str.substr(pos,m_index-pos);
}

std::string Parser::parse_element_attr_key() {
    int pos = m_index;
    if (isalnum(m_str[m_index]) || m_str[m_index] == '_') {
        m_index++;
        while (isalnum(m_str[m_index]) || m_str[m_index] == '_' || m_str[m_index] == '-' || m_str[m_index] == ':') {
            m_index++;
        }
    }
    return m_str.substr(pos,m_index - pos);
}

std::string Parser::parse_element_attr_value() {
    if (m_str[m_index] != '"') {
        throw std::logic_error("parse attr value error");
    }
    m_index++;
    int pos  = m_index;
    while (m_str[m_index] != '"') {
        m_index++;
    }
    m_index++;
    return m_str.substr(pos,m_index - pos-1);
}











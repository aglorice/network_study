//
// Created by aglorice on 2026/1/2.
//

#ifndef NETWORK_STUDY_XML_H
#define NETWORK_STUDY_XML_H
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include <fstream>
#include "../utility/value.h"

using namespace yazi::utility;

namespace yazi {
    namespace xml {
        class Xml {
        public:
            Xml() = default;
            Xml(const char *name);
            Xml(const std::string &name);
            Xml(const Xml & other);
            Xml(Xml&&other);
            ~Xml();

            [[nodiscard]] std::string name() const;
            void name(const std::string &name);

            [[nodiscard]] std::string text() const;
            void text(const std::string &text);

            Value & attr(const std::string&key );
            void attr(const std::string &key,const Value&value);

            void append(const Xml &child);
            void append(Xml&&child);
            void remove(int index);
            void remove(const char*name);
            void remove(const std::string &name);

            Xml& operator[](int index);
            Xml& operator[](const char*name);
            Xml& operator[](const std::string &name);
            Xml& operator=(const Xml &other);
            Xml& operator=(Xml&&other);

            int size() const;
            bool empty() const;
            void clear();

            typedef std::vector<Xml>::iterator iterator;
            iterator begin() {
                return m_child.begin();
            }

            iterator end() {
                return m_child.end();
            }

            iterator erase(iterator it) {
                it->clear();
                return m_child.erase(it);
            }

            [[nodiscard]] std::string str() const;
            friend std::ostream & operator << (std::ostream &os,const Xml &xml) {
                os <<xml.str();
                return os;
            }

            bool load(const std::string & filename);
            bool load(const char * buff,int len);
            [[nodiscard]] bool save(const std::string & filename) const;
        private:
            void copy(const Xml &xml);
            void swap(Xml&other);
        private:
            std::string m_name;
            std::string m_text;
            std::map<std::string,Value> m_attrs;
            std::vector<Xml> m_child;
        };
    }
}
#endif //NETWORK_STUDY_XML_H
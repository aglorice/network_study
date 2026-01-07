//
// Created by aglorice on 2025/12/17.
//

#ifndef NETWORK_STUDY_INI_FILE_H
#define NETWORK_STUDY_INI_FILE_H
#include <map>
#include <fstream>
#include <stdexcept>
#include <sstream>

#include "value.h"


namespace yazi {
    namespace utility {
        class IniFile {
            typedef std::map<std::string,Value> Section;
        public:
            IniFile() = default;
            explicit IniFile(const std::string & filename);
            ~IniFile() = default;

            bool load(const std::string & filename);

            [[nodiscard]] std::string str() const;
            void show() const;

            Value & get (const std::string & section,const std::string & key);
            void set(const std::string & section,const std::string & key,const Value &val);

            Section & operator[] (const std::string &section) {
                return m_sections[section];
            }

            bool has(const std::string &section);
            bool has(const std::string &section,const std::string &key);

            void remove(const std::string &section);
            void remove(const std::string &section,const std::string &key);

            void clear();
            void save(const std::string &filename);
        private:
            std::string trim(std::string s);
        private:
            std::string m_filename;
            std::map<std::string,Section> m_sections;
        };
    }
}

#endif //NETWORK_STUDY_INI_FILE_H
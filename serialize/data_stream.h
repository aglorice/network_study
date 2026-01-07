//
// Created by aglorice on 2026/1/3.
//

#ifndef NETWORK_STUDY_DATA_STREAM_H
#define NETWORK_STUDY_DATA_STREAM_H
#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <list>
#include <map>
#include <set>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "serializable.h"


namespace yazi {
    namespace serialize {
        class DataStream {
        public:
            enum DateType {
                BOOL = 0,
                CHAR,
                INT32,
                INT64,
                FLOAT,
                DOUBLE,
                STRING,
                VECTOR,
                LIST,
                MAP,
                SET,
                CUSTOM
            };
            enum ByteOrder {
                BigEndian = 0,
                LittleEndian
            };

            DataStream();
            ~DataStream() = default;

            void write(bool value);
            void write(char value);
            void write(int32_t value);
            void write(int64_t value);
            void write(const char * value);
            void write(const std::string & value);
            void write(float value);
            void write(double value);
            void write(const Serializable &serializable);
            void write(const char *data,int len);

            template<typename T,typename ...Args>
            void write_args(const T&head,const Args&... args) {
                write(head);
                write_args(args...);
            }

            template<typename T,typename ...Args>
            void read_args(T&head,Args&... args) {
                read(head);
                read_args(args...);
            }

            void write_args() {}
            void read_args() {}

            DataStream & operator<< (const bool &value);
            DataStream & operator<< (const int32_t &value);
            DataStream & operator<< (const int64_t &value);
            DataStream & operator<< (const char &value);
            DataStream & operator<< (const float &value);
            DataStream & operator<< (const double &value);
            DataStream & operator<< (const char * value);
            DataStream & operator<< (const std::string &value);
            DataStream& operator << (const Serializable &serializable);

            template<typename T>
            DataStream & operator << (const std::vector<T> & value) {
                write(value);
                return *this;
            }

            template<typename K,typename V>
            DataStream & operator << (const std::map<K,V> & value){
                write(value);
                return *this;
            }

            template<typename T>
            DataStream & operator << (const std::list<T> & value){
                write(value);
                return *this;
            }

            template<typename T>
            DataStream & operator << (const std::set<T> & value){
                write(value);
                return *this;
            }


            void show();

            template<typename T>
            void write(const std::vector<T> &value) {
                char type = DateType::VECTOR;
                write(&type,sizeof(char));
                int32_t len = value.size();
                write(len);
                for (int32_t i = 0;i<len;i++) {
                    write(value[i]);
                }
            }

            template<typename T>
            void write(const std::list<T> &value) {
                char type = DateType::LIST;
                write(&type,sizeof(char));
                int32_t len = value.size();
                write(len);
                for (int32_t i = 0;i<len;i++) {
                    write(value[i]);
                }
            }

            template<typename T>
            void write(const std::set<T> &value) {
                char type = DateType::SET;
                write(&type,sizeof(char));
                int32_t len = value.size();
                write(len);
                for (int32_t i = 0;i<len;i++) {
                    write(value[i]);
                }
            }


            template<typename K, typename V>
            void write(const std::map<K, V> &value) {
                char type  = DateType::MAP;
                write(&type,sizeof(char));
                int32_t len = value.size();
                write(len);
                for (auto it = value.begin();it!=value.end();++it) {
                    write(it->first);
                    write(it->second);
                }
            }
            bool read(char *data,int len);
            bool read(bool &value);
            bool read(char &value);
            bool read(int32_t &value);
            bool read(int64_t &value);
            bool read(float &value);
            bool read(double &value);
            bool read(std::string &value);
            bool read(Serializable &value);




            template<typename K, typename V>
            bool read(std::map<K, V> &value) {
                value.clear();
                if (m_buf[m_pos] != DateType::MAP) {
                    return false;
                }
                ++m_pos;
                int32_t len = 0;
                read(len);
                for (int i = 0;i<len;i++) {
                    K key;
                    V val;
                    read(key);
                    read(val);
                    value[key] = val;
                }
                return true;
            }

            template<typename T>
            bool read(std::list<T> &value) {
                value.clear();
                if (m_buf[m_pos] != DateType::LIST) {
                    return false;
                }
                ++m_pos;
                int32_t len = 0;
                read(len);
                for (int i = 0;i<len;i++) {
                    T val;
                    read(val);
                    value.push_back(val);
                }
                return true;
            }

            template<typename T>
            bool read(std::set<T> &value) {
                value.clear();
                if (m_buf[m_pos] != DateType::MAP) {
                    return false;
                }
                ++m_pos;
                int32_t len = 0;
                read(len);
                for (int i = 0;i<len;i++) {
                    T val;
                    read(val);
                    value.insert(val);
                }
                return false;
            }

            template<typename T>
            bool read(std::vector<T> &value) {
                value.clear();
                if (m_buf[m_pos] != DateType::VECTOR) {
                    return false;
                }
                ++m_pos;
                int32_t len = 0;
                read(len);
                for (int i = 0;i<len;i++) {
                    T val;
                    read(val);
                    value.push_back(val);
                }
                return true;
            }

            DataStream & operator>> (bool &value);
            DataStream & operator>> (int32_t &value);
            DataStream & operator>> (int64_t &value);
            DataStream & operator>> (char &value);
            DataStream & operator>> (float &value);
            DataStream & operator>> (double &value);
            DataStream & operator>> (std::string &value);
            DataStream & operator >> (Serializable &serializable);

            template<typename T>
            DataStream & operator >> (std::vector<T> & value){
                read(value);
                return *this;
            }

            template<typename K,typename V>
            DataStream & operator >> (std::map<K,V> & value){
                read(value);
                return *this;
            }

            template<typename T>
            DataStream & operator >> (std::list<T> & value){
                read(value);
                return *this;
            }

            template<typename T>
            DataStream & operator >> (std::set<T> & value){
                read(value);
                return *this;
            }

            [[nodiscard]] const char * data() const;
            [[nodiscard]] int size() const;
            void reset();
            void clear();
            void save(const std::string &filename);
            void load(const std::string &filename);

            [[nodiscard]] ByteOrder byteOrder() const {
                return m_byteorder;
            }

        private:
            void reserve(int len);
            ByteOrder byteorder();
        private:
            std::vector<char> m_buf;
            int m_pos;
            ByteOrder m_byteorder;
        };
    }
}

#endif //NETWORK_STUDY_DATA_STREAM_H
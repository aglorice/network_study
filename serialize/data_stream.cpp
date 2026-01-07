//
// Created by aglorice on 2026/1/3.
//

#include "data_stream.h"

using namespace yazi::serialize;

DataStream::DataStream() : m_pos(0) {
    m_byteorder = byteorder();
}



void DataStream::reserve(int len) {
    int size = m_buf.size();
    int cap = m_buf.capacity();
    if (size + len > cap) {
        while (size + len > cap) {
            if (cap == 0) {
                cap = 1;
            }else {
                cap *= 2;
            }
        }
        m_buf.reserve(cap);
    }
}


void DataStream::write(const char *data, int len) {
    reserve(len);
    int size = m_buf.size();
    m_buf.resize(m_buf.size()+len);
    std::memcpy(&m_buf[size],data,len);
}


void DataStream::write(bool value) {
    char type = DateType::BOOL;
    write((char*)&type,sizeof(char));
    write((char*)&value,sizeof(char));
}

void DataStream::write(char value) {
    char type = DateType::CHAR;
    write((char*)&type,sizeof(char));
    write((char*)&value,sizeof(char));
}

void DataStream::write(const char *value) {
    char type = DateType::STRING;
    write((char*)&type,sizeof(char));
    int32_t len = strlen(value);
    write(len);
    write(value,len);
}

void DataStream::write(const std::string &value) {
    write(value.c_str());
}

void DataStream::write(double value) {
    char type = DateType::DOUBLE;
    write((char*)&type,sizeof(char));
    if (m_byteorder == ByteOrder::BigEndian) {
        char *first = (char*)&value;
        char *last = first + sizeof(double);
        std::reverse(first,last);
    }
    write((char*)&value,sizeof(double));
}

void DataStream::write(float value) {
    char type = DateType::FLOAT;
    write((char*)&type,sizeof(char));
    if (m_byteorder == ByteOrder::BigEndian) {
        char *first = (char*)&value;
        char *last = first + sizeof(float);
        std::reverse(first,last);
    }
    write((char*)&value,sizeof(float));
}

void DataStream::write(int32_t value) {
    char type = DateType::INT32;
    write((char*)&type,sizeof(char));
    if (m_byteorder == ByteOrder::BigEndian) {
        char *first = (char*)&value;
        char *last = first + sizeof(int32_t);
        std::reverse(first,last);
    }
    write((char*)&value,sizeof(int32_t));
}

void DataStream::write(int64_t value) {
    char type = DateType::INT64;
    write((char*)&type,sizeof(char));
    if (m_byteorder == ByteOrder::BigEndian) {
        char *first = (char*)&value;
        char *last = first + sizeof(int64_t);
        std::reverse(first,last);
    }
    write((char*)&value,sizeof(int64_t));
}

void DataStream::show() {
    int size = m_buf.size();
    std::cout << "data size = " << size << std::endl;
    int i = 0;
    while (i< size) {
        switch ((DateType)m_buf[i]) {
            case BOOL:
                if ((int)m_buf[++i] == 0) {
                    std::cout << "false";
                }else {
                    std::cout << "true";
                }
                ++i;
                break;
            case CHAR:
                std::cout << m_buf[++i];
                ++i;
                break;
            case INT32:
                std::cout << *(int32_t*)(&m_buf[++i]);
                i+=sizeof(int32_t);
                break;
            case INT64:
                std::cout << *(int64_t*)(&m_buf[++i]);
                i+=sizeof(int64_t);
                break;
            case DOUBLE:
                std::cout << *(double*)(&m_buf[++i]);
                i+=sizeof(double);
                break;
            case FLOAT:
                std::cout << *(float*)(&m_buf[++i]);
                i+=sizeof(float);
                break;
            case STRING:
                if ((DateType)m_buf[++i] == DateType::INT32) {
                    int len = *(int32_t*)(&m_buf[++i]);
                    i+=sizeof(int32_t);
                    std::cout << std::string(&m_buf[i],len);
                    i+=len;
                }else {
                    throw std::logic_error("invalid string length");
                }
                break;
            default:
                std::cout << "invalid data value";
                break;
        }
    }

}


bool DataStream::read(bool &value) {
    if (m_buf[m_pos] != DateType::BOOL) {
        return false;
    }
    ++m_pos;
    value = m_buf[m_pos];
    ++m_pos;
    return true;
}

bool DataStream::read(char &value) {
    if (m_buf[m_pos] != DateType::CHAR) {
        return false;
    }
    ++m_pos;
    value = m_buf[m_pos];
    ++m_pos;
    return true;
}

bool DataStream::read(double &value) {
    if (m_buf[m_pos] != DateType::DOUBLE) {
        return false;
    }
    ++m_pos;
    value = *((double*)(&m_buf[m_pos]));
    if (m_byteorder == ByteOrder::BigEndian) {
        char *first = (char*)&value;
        char *last = first + sizeof(double);
        std::reverse(first,last);
    }
    m_pos += sizeof(double);
    return true;
}

bool DataStream::read(float &value) {
    if (m_buf[m_pos] != DateType::FLOAT) {
        return false;
    }
    ++m_pos;
    value = *((float*)(&m_buf[m_pos]));
    if (m_byteorder == ByteOrder::BigEndian) {
        char *first = (char*)&value;
        char *last = first + sizeof(float);
        std::reverse(first,last);
    }
    m_pos += sizeof(float);
    return true;
}

bool DataStream::read(int32_t &value) {
    if (m_buf[m_pos] != DateType::INT32) {
        return false;
    }
    ++m_pos;
    value = *((int32_t*)(&m_buf[m_pos]));
    if (m_byteorder == ByteOrder::BigEndian) {
        char *first = (char*)&value;
        char *last = first + sizeof(int32_t);
        std::reverse(first,last);
    }
    m_pos += sizeof(int32_t);
    return true;
}

bool DataStream::read(int64_t &value) {
    if (m_buf[m_pos] != DateType::INT32) {
        return false;
    }
    ++m_pos;
    value = *((int32_t*)(&m_buf[m_pos]));
    if (m_byteorder == ByteOrder::BigEndian) {
        char *first = (char*)&value;
        char *last = first + sizeof(int64_t);
        std::reverse(first,last);
    }
    m_pos += sizeof(int64_t);
    return true;
}

bool DataStream::read(std::string &value) {
    if (m_buf[m_pos] != DateType::STRING) {
        return false;
    }
    ++m_pos;
    int32_t len = 0;
    read(len);
    if (len < 0) {
        return false;
    }
    value.assign((char*)&(m_buf[m_pos]),len);
    m_pos +=len;
    return true;
}

DataStream &DataStream::operator<<(const bool &value) {
    write(value);
    return *this;
}

DataStream &DataStream::operator<<(const char &value) {
    write(value);
    return *this;
}

DataStream &DataStream::operator<<(const char *value) {
    write(value);
    return *this;
}

DataStream &DataStream::operator<<(const double &value) {
    write(value);
    return *this;
}

DataStream &DataStream::operator<<(const float &value) {
    write(value);
    return *this;
}

DataStream &DataStream::operator<<(const int32_t &value) {
    write(value);
    return *this;
}

DataStream &DataStream::operator<<(const int64_t &value) {
    write(value);
    return *this;
}

DataStream &DataStream::operator<<(const std::string &value) {
    write(value);
    return *this;
}


DataStream &DataStream::operator>>(bool &value) {
    read(value);
    return *this;
}


DataStream &DataStream::operator>>(char &value) {
    read(value);
    return *this;
}

DataStream &DataStream::operator>>(int32_t &value) {
    read(value);
    return *this;
}

DataStream &DataStream::operator>>(int64_t &value) {
    read(value);
    return *this;
}

DataStream &DataStream::operator>>(float &value) {
    read(value);
    return *this;
}

DataStream &DataStream::operator>>(double &value) {
    read(value);
    return *this;
}

DataStream &DataStream::operator>>(std::string &value) {
    read(value);
    return *this;
}


bool DataStream::read(char *data, int len) {
    std::memcpy(data,(char*)&m_buf[m_pos],len);
    m_pos +=len;
    return true;
}

bool DataStream::read(Serializable &value) {
    return value.unserialize(*this);
}

void DataStream::write(const Serializable &serializable) {
    serializable.serialize(*this);
}



DataStream &DataStream::operator<<(const Serializable &serializable) {
    write(serializable);
    return *this;
}

DataStream &DataStream::operator>>(Serializable &serializable) {
    read(serializable);
    return *this;
}

const char *DataStream::data() const {
    return m_buf.data();
}

int DataStream::size() const {
    return m_buf.size();
}

void DataStream::clear() {
    m_buf.clear();
    m_pos = 0;
}

void DataStream::reset() {
    m_pos = 0;
}

void DataStream::load(const std::string &filename) {
    std::ifstream ifs(filename);
    std::ostringstream oss;
    if (ifs.fail()) {
        throw std::logic_error("open file fail: "+filename);
    }
    oss << ifs.rdbuf();
    const std::string &str = oss.str();
    reserve(str.size());
    write(str.data(),str.size());
    ifs.close();
}

void DataStream::save(const std::string &filename) {
    std::ofstream ofs(filename);
    if (ofs.fail()) {
        throw std::logic_error("open file fail: "+filename);
    }
    ofs.write(data(),size());
    ofs.flush();
    ofs.close();
}

DataStream::ByteOrder DataStream::byteorder() {
    int n = 0x12345678;
    char str[4] = {0};
    std::memcpy(str,&n,sizeof(int));
    if (str[0] == 0x12) {
        return ByteOrder::BigEndian;
    }
    return ByteOrder::LittleEndian;
}











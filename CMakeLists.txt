cmake_minimum_required(VERSION 4.0)
project(network_study)

set(CMAKE_CXX_STANDARD 20)

add_executable(network_study main.cpp
        utility/option.h
        utility/option.cpp
        utility/value.h
        utility/value.cpp
        utility/ini_file.h
        utility/ini_file.cpp
        utility/logger.h
        utility/logger.cpp
        utility/singleton.h
        test/a.h
        stl/vector.h
        utility/time.h
        utility/time.cpp
        utility/string.h
        utility/string.cpp
        json/json.h
        json/json.cpp
        json/parser.h
        json/parser.cpp
        xml/xml.h
        xml/xml.cpp
        xml/parser.h
        xml/parser.cpp
        serialize/data_stream.h
        serialize/data_stream.cpp
        serialize/serializable.h
        serialize/serializable.cpp
        reflect/class_factory.h
        reflect/class_factory.cpp
        reflect/class_register.h
        reflect/class_field.h
        reflect/class_method.h
        fs/file.h
        fs/file.cpp
        fs/directory.h
        fs/directory.cpp
)

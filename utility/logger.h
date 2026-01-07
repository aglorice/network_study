//
// Created by aglorice on 2025/12/17.
//

#ifndef NETWORK_STUDY_LOGGER_H
#define NETWORK_STUDY_LOGGER_H

#include <string>
#include <fstream>
#include <ctime>
#include <iostream>
#include <sstream>
#include <cstdarg>
#include "singleton.h"

#ifdef WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif


namespace yazi {
    namespace utility {
    #define log_debug(format,...)\
        Singleton<Logger>::instance()->log(Logger::LOG_DEBUG,__FILE__,__LINE__,format,##__VA_ARGS__)

    #define log_info(format,...)\
        Singleton<Logger>::instance()->log(Logger::LOG_INFO,__FILE__,__LINE__,format,##__VA_ARGS__)

    #define log_warn(format,...)\
        Singleton<Logger>::instance()->log(Logger::LOG_WARN,__FILE__,__LINE__,format,##__VA_ARGS__)

    #define log_error(format,...)\
        Singleton<Logger>::instance()->log(Logger::LOG_ERROR,__FILE__,__LINE__,format,##__VA_ARGS__)

    #define log_fatal(format,...)\
        Singleton<Logger>::instance()->log(Logger::LOG_FATAL,__FILE__,__LINE__,format,##__VA_ARGS__)
        
        class Logger {
            SINGLETON(Logger);
        private:
            Logger() = default;
            ~Logger();
        public:
            enum Level {
                LOG_DEBUG = 0,
                LOG_INFO,
                LOG_WARN,
                LOG_ERROR,
                LOG_FATAL,
                LOG_COUNT
            };

            void open(const std::string & filename);
            void close();
            void log(Level level,const char *file,int line,const char *format,...);

            void set_level(Level level);
            void set_max_size(int size);
            void set_console(bool console);
        private:
            void rotate();
            void localtime(struct  tm * time_info,time_t *ticks);
            void sleep(int milliseconds);
        private:
            std::string m_filename;
            std::ofstream m_ofs;
            bool m_console = true;
            int m_max = 0;
            int m_len = 0;
            int m_level = LOG_DEBUG;
            static const char * s_level[LOG_COUNT];
        };
    }
}


#endif //NETWORK_STUDY_LOGGER_H
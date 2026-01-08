//
// Created by aglorice on 2025/12/18.
//

#ifndef NETWORK_STUDY_SINGLETON_H
#define NETWORK_STUDY_SINGLETON_H

namespace yazi {
    namespace utility {
        template <typename T>
        class Singleton {
        private:
            Singleton() = default;
            ~Singleton() = default;
        public:
            // 这些方法应该放在公有方法中，报错更加明显，意图清晰
            Singleton(const Singleton<T> &) = delete;
            Singleton & operator=(const Singleton<T> &) = delete;
        public:
            static T * instance() {
                static T instance;
                return &instance;
            }
        };
#define SINGLETON(classname)                                    \
        friend class Singleton<classname>;                      \
        public:                                                 \
            classname & operator = (const classname &) = delete;\
            classname(const classname &)  = delete;             \
            classname() = default

    }
}

#endif //NETWORK_STUDY_SINGLETON_H
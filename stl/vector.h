//
// Created by aglorice on 2025/12/18.
//

#ifndef NETWORK_STUDY_VECTOR_H
#define NETWORK_STUDY_VECTOR_H

#include <stdexcept>

namespace yazi {
    namespace stl {
        template<typename T>
        class Vector {
        public:
            Vector();
            ~Vector();

            Vector(const Vector &other);
            Vector& operator = (const Vector<T> & other);

            void push_back(const T & value);
            void pop_back();

            T& at(int index);
            const T & at(int index) const;

            T& front();
            const T &front() const;
            T& back();
            const T &back() const;

            bool empty() const noexcept;
            void clear() noexcept;
            int size() const noexcept;
            int capacity() const noexcept;

            T* data() noexcept;
            const T * data() const noexcept;

            T& operator[](int index);
            const T& operator[](int index) const;

            void swap(Vector &other);

            void resize(int size);
            void resize(int n,const T &val);
            void reserve(int n);

            class iterator {
            public:
                iterator() : m_pointer(nullptr) {

                }
                iterator(T * pointer) : m_pointer(pointer) {}
                ~iterator() = default;

                bool operator==(const iterator & other) const {
                    return m_pointer == other.m_pointer;
                }

                bool operator!=(const iterator &other) const{
                    return m_pointer != other.m_pointer;
                }
                iterator & operator = (const iterator & other) {
                    m_pointer = other.m_pointer;
                    return *this;
                }
                // 前缀加加
                iterator & operator ++() {
                    m_pointer+=1;
                    return *this;
                }

                iterator operator ++(int) {
                    iterator it = *this;
                    ++(*this);
                    return it;
                }

                iterator operator +(int i) {
                    iterator it = *this;
                    it.m_pointer += i;
                    return it;
                }

                iterator & operator += (int i) {
                    m_pointer += i;
                    return *this;
                }

                // 前缀加加
                iterator & operator --() {
                    m_pointer-=1;
                    return *this;
                }

                iterator operator --(int) {
                    iterator it = *this;
                    --(*this);
                    return it;
                }

                iterator operator -(int i) {
                    iterator it = *this;
                    it.m_pointer -= i;
                    return it;
                }

                iterator & operator -= (int i) {
                    m_pointer  -= i;
                    return *this;
                }

                int operator -(const iterator & other) const {
                    return m_pointer- other.m_pointer;
                }

                T & operator *() {
                    return *m_pointer;
                }

                T * operator -> () {
                    return m_pointer;
                }

            private:
                T * m_pointer;
            };

            class reverse_iterator {
            public:
                reverse_iterator() : m_pointer(nullptr){}
                reverse_iterator(T * pointer) : m_pointer(pointer){}
                ~reverse_iterator() =default;

                bool operator==(const reverse_iterator &other) const {
                    return m_pointer == other.m_pointer;
                }

                bool operator!=(const reverse_iterator &other) const {
                    return m_pointer != other.m_pointer;
                }

                reverse_iterator& operator ++() {
                    m_pointer-=1;
                    return *this;
                }

                reverse_iterator& operator ++(int) {
                    reverse_iterator it = *this;
                    ++(*this);
                    return it;
                }
                reverse_iterator operator + (int i) {
                    reverse_iterator it = *this;
                    it.m_pointer -= i;
                    return it;
                }

                reverse_iterator operator +=(int i) {
                    m_pointer -= i;
                    return *this;
                }

                // 前缀 --
                reverse_iterator& operator --() {
                    m_pointer+=1;
                    return *this;
                }
                // 后缀 --
                reverse_iterator& operator --(int) {
                    reverse_iterator it = *this;
                    --(*this);
                    return it;
                }

                reverse_iterator operator - (int i) {
                    reverse_iterator it = *this;
                    it.m_pointer += i;
                    return it;
                }

                reverse_iterator operator -= (int i) {
                    m_pointer+=i;
                    return *this;
                }

                T & operator *() {
                    return *m_pointer;
                }

                T* operator -> () {
                    return m_pointer;
                }

            private:
                T * m_pointer;
            };
            reverse_iterator rbegin() noexcept;
            reverse_iterator rend() noexcept;

            void show() const;
            iterator begin() noexcept;
            iterator end() noexcept;

            iterator insert(iterator pos,const T & value);
            iterator insert(iterator pos,int n,const T & value);

            iterator erase (iterator pos);
            iterator erase(iterator first,iterator last);
        private:
            T * m_date;
            int m_size;
            int m_capacity;
        };
        template<typename T>
        Vector<T>::Vector() : m_date(nullptr) , m_size(0),m_capacity(0)  {

        }

        template<typename T>
        Vector<T>::Vector(const Vector &other) {
            m_size = other.m_size;
            m_capacity = other.m_capacity;

            if (m_capacity > 0) {
                m_date = new T[m_capacity];
                for (int i = 0 ;i < m_size ;i++) {
                    m_date[i] = other.m_date[i];
                }
            }else {
                m_date = nullptr;
            }
        }

        template<typename T>
        Vector<T> &Vector<T>::operator=(const Vector<T> &other) {
            if (&other == this) {
                return *this;
            }

            if (m_capacity < other.m_size) {
                T*new_date = new T[other.m_capacity];

                if (m_date != nullptr) {
                    delete [] m_date;
                }
                m_date = new_date;
                m_capacity = other.m_capacity;

            }
            for (int i = 0;i<other.m_size;i++) {
                m_date = other.m_date[i];
            }
            m_size = other.m_size;
            return *this;
        }


        template<typename T>
        Vector<T>::~Vector() {
            if (m_date != nullptr) {
                delete [] m_date;
                m_date = nullptr;
            }
            m_size = 0;
            m_capacity = 0;
        }


        template<typename T>
        void Vector<T>::push_back(const T &value) {
            if (m_size < m_capacity) {
                m_date[m_size++] = value;
                return;
            }

            // 对vector尽心扩容，每次不够了就将存储空间翻倍
            if (m_capacity == 0) {
                m_capacity = 1;
            }else {
                m_capacity *= 2;
            }
            T * data = new T[m_capacity];
            for (int i = 0;i<m_size;i++) {
                data[i] = m_date[i];
            }
            if (m_date != nullptr) {
                delete [] m_date;
                m_date = nullptr;
            }
            m_date = data;
            m_date[m_size] = value;
            m_size++;
        }


        template<typename T>
        void Vector<T>::pop_back() {
            if (m_size>0) {
                m_size--;
            }
        }

        template<typename T>
        T &Vector<T>::at(int index) {
            if (index < 0 || index >= m_size) {
                throw std::logic_error("out of range");
            }
            return m_date[index];
        }

        template<typename T>
        const T &Vector<T>::at(int index) const {
            if (index < 0 || index >= m_size) {
                throw std::logic_error("out of range");
            }
            return m_date[index];
        }

        template<typename T>
        T &Vector<T>::front() {
            if (m_size <= 0) {
                throw std::logic_error("vector is empty");
            }
            return m_date[0];
        }

        template<typename T>
        const T &Vector<T>::front() const {
            if (m_size <= 0) {
                throw std::logic_error("vector is empty");
            }
            return m_date[0];
        }


        template<typename T>
        T &Vector<T>::back() {
            if (m_size <= 0) {
                throw std::logic_error("vector is empty");
            }
            return m_date[m_size-1];
        }

        template<typename T>
        const T &Vector<T>::back() const {
            if (m_size <= 0) {
                throw std::logic_error("vector is empty");
            }
            return m_date[m_size-1];
        }

        template<typename T>
        bool Vector<T>::empty() const noexcept {
            return m_size == 0;
        }

        template<typename T>
        void Vector<T>::clear() noexcept {
            m_size = 0;
        }

        template<typename T>
        int Vector<T>::capacity() const noexcept {
            return m_capacity;
        }

        template<typename T>
        int Vector<T>::size() const noexcept {
            return m_size;
        }

        template<typename T>
        T *Vector<T>::data() noexcept {
            return m_date;
        }

        template<typename T>
        const T *Vector<T>::data() const noexcept {
            return m_date;
        }

        template<typename T>
        T &Vector<T>::operator[](int index) {
            if (index <0 || index >= m_size) {
                throw std::logic_error("out of range");
            }
            return m_date[index];
        }

        template<typename T>
        const T &Vector<T>::operator[](int index) const {
            if (index <0 || index >= m_size) {
                throw std::logic_error("out of range");
            }
            return m_date[index];
        }

        template<typename T>
        void Vector<T>::swap(Vector &other) {
            T * data = other.m_date;
            int size = other.m_size;
            int capacity = other.m_capacity;

            other.m_date = m_date;
            other.m_size = m_size;
            other.m_capacity = m_capacity;

            m_date = data;
            m_size = size;
            m_capacity = capacity;
        }

        template<typename T>
        void Vector<T>::resize(int size) {
            if (m_size > size) {
                m_size = size;
                return;
            }
            if (size <= m_capacity) {
                for (int i = m_size;i<size;i++) {
                    m_date[i] = T();
                }
                m_size = size;
                return;
            }
            while (m_capacity < size) {
                if (m_capacity == 0) {
                    m_capacity =1;
                }else {
                    m_capacity*=2;
                }
            }

            T *data = new T[m_capacity];
            for (int i =0;i<m_size;i++) {
                data[i] = m_date[i];
            }
            for (int i = m_size;i<size;i++) {
                data[i] = T();
            }
            if (m_date != nullptr) {
                delete [] m_date;
                m_date = nullptr;
            }
            m_date = data;
            m_size = size;
        }


        template<typename T>
        void Vector<T>::resize(int size, const T &val) {
            if (m_size > size) {
                m_size = size;
                return;
            }
            if (size <= m_capacity) {
                for (int i = m_size;i<size;i++) {
                    m_date[i] = val;
                }
                m_size = size;
                return;
            }
            while (m_capacity < size) {
                if (m_capacity == 0) {
                    m_capacity =1;
                }else {
                    m_capacity*=2;
                }
            }

            T *data = new T[m_capacity];
            for (int i =0;i<m_size;i++) {
                data[i] = m_date[i];
            }
            for (int i = m_size;i<size;i++) {
                data[i] = val;
            }
            if (m_date != nullptr) {
                delete [] m_date;
                m_date = nullptr;
            }
            m_date = data;
            m_size = size;
        }
        template<typename T>
        void Vector<T>::reserve(int n) {
            if (m_capacity>=n) {
                return;
            }
            while (m_capacity < n) {
                if (m_capacity == 0) {
                    m_capacity = 1;
                }else {
                    m_capacity *= 2;
                }
            }
            T *data = new T[m_capacity];
            for (int i = 0;i<m_size;i++) {
                data[i] = m_date[i];
            }
            if (m_date != nullptr) {
                delete m_date;
            }
            m_date = data;
        }

        template<typename T>
        Vector<T>::iterator Vector<T>::begin() noexcept {
            iterator it(m_date);
            return it;
        }

        template<typename T>
        Vector<T>::iterator Vector<T>::end() noexcept {
            iterator it(m_date+m_size);
            return it;
        }

        template<typename T>
        Vector<T>::reverse_iterator Vector<T>::rbegin() noexcept {
            reverse_iterator it(m_date+m_size-1);
            return it;
        }

        template<typename T>
        Vector<T>::reverse_iterator Vector<T>::rend() noexcept {
            reverse_iterator it(m_date-1);
            return it;
        }

        template<typename T>
        Vector<T>::iterator Vector<T>::insert(iterator pos, const T &value) {
            return insert(pos,1,value);
        }

        template<typename T>
        Vector<T>::iterator Vector<T>::insert(iterator pos, int n, const T &value) {
            int size = pos - begin();

            if (m_size + n <= m_capacity) {
                for (int i = m_size;i>size;i--) {
                    m_date[i+n-1] = m_date[i-1];
                }
                for (int i = 0;i<n;i++) {
                    m_date[size+i] = value;
                }
                m_size+=n;
                return Vector<T>::iterator(m_date+size);
            }

            while (m_size +n > m_capacity) {
                if (m_capacity == 0) {
                    m_capacity = 1;
                }else {
                    m_capacity*=2;
                }
            }
            T*data = new T[m_capacity];
            for (int i = 0;i< size;i++) {
                data[i] = m_date[i];
            }
            for (int i = 0;i<n;i++) {
                data[size+i] = value;
            }
            for (int i = size;i<m_size;i++) {
                data[i+n] = m_date[i];
            }
            if (m_date != nullptr) {
                delete [] m_date;
                m_date = nullptr;
            }
            m_date = data;
            m_size = m_size+ n;
            return Vector<T>::iterator(m_date+size);
        }


        template<typename T>
        Vector<T>::iterator Vector<T>::erase(iterator first, iterator last) {
            int f = first-begin();
            int l = last-begin();
            int n = last-first;
            for (int i = 0;i<m_size - l;i++) {
                m_date[f + i] = m_date[l+i];
            }
            m_size -= n;
            return first;
        }

        template<typename T>
        Vector<T>::iterator Vector<T>::erase(iterator pos) {
            if (end() - pos == 1) {
                // 这里是删除最后一个元素
                m_size--;
                return  end();
            }
            int size = pos - end();
            for (int i=size;i<m_size-1;i++) {
                m_date[i] = m_date[i+1];
            }
            m_size -=1;
            return pos;

        }




        template <typename  T>
        void Vector<T>::show() const{
            std::cout << "size = " << m_size << ", capacity = " << m_capacity << std::endl;
            for (int i = 0;i < m_size;i++) {
                std::cout << m_date[i] << ", ";
            }
            std::cout << std::endl;
        }
    }
}
#endif //NETWORK_STUDY_VECTOR_H
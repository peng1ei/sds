#ifndef SDS_VECTOR_H
#define SDS_VECTOR_H
#include <cassert>
#include <cstddef>
#include <initializer_list>
#include <iterator>
#include <iostream>

namespace sds {

    template <typename T>
    class Vector {
    public:
        // 迭代器本身是一个对象，表示的是某个元素在容器中的位置。
        template <typename IterT>
        struct VectorIter : public std::iterator<std::random_access_iterator_tag, IterT> {
            typedef VectorIter<IterT> self;

            IterT *p_item_;

            VectorIter() : p_item_(nullptr) {}
            explicit VectorIter(IterT *p_item) : p_item_(p_item) {}

            // deference
            // 通过迭代器访问容器中的元素
            IterT& operator*() const {
                return *(p_item_);
            }
            
            // member access
            // 通过迭代器访问容器中元素本身的成员
            IterT* operator->() const {
                return &(operator*());
            }

            // 前置自增，++i
            self& operator++() {
                ++p_item_;
                return *this;
            }

            // 后置自增，i++
            self operator++(int) {
                self tmp = *this;
                ++(*this);
                return tmp;
            } 
            
            // 前置自减，--i
            self& operator--() {
                --p_item_;
                return *this;
            }

            // 后置自减，i--
            self operator--(int) {
                self tmp = *this;
                --(*this);
                return *this;
            }

            self operator+(int off) const {
                self tmp = *this;
                return (tmp += off);
            }

            self& operator+=(int off) {
                p_item_ += off;
                return *this;
            }
            
            self operator-(int off) const {
                self tmp = *this;
                return (tmp -= off);
            }

            self& operator-=(int off) {
                p_item_ -= off;
                return *this; 
            }

            // 注意：不允许两个指针相加，无意义
            // 两个指针相减，表示的是两个指针之间的元素的个数
            size_t operator-(const self &other) const {
                return size_t(p_item_ - other.p_item_);
            }

            // 逻辑运算符
            bool operator<(const self &other) const {
                return p_item_ < other.p_item_;
            }

            bool operator>(const self &other) const {
                return p_item_ > other.p_item_;
            }

            bool operator<=(const self &other) const {
                return p_item_ <= other.p_item_;
            }

            bool operator>=(const self &other) const {
                return p_item_ >= other.p_item_;
            }

            bool operator==(const self &other) const {
                return p_item_ == other.p_item_;
            }

            bool operator!=(const self &other) const {
                return p_item_ != other.p_item_;
            }

            // [offset]，支持随机访问，不改变迭代器本身的位置，只是基于当前迭代器
            // 的位置和给定的偏移量来随机访问容器中的元素。
            // Use of offset dereference operator ([ ]): 
            // Random-access iterators support offset dereference operator ([ ])
            IterT& operator[](int off) { return *(p_item_ + off); }            
            const IterT& operator[](int off) const { return *(p_item_ + off); }

            IterT* base() { return p_item_; }
            const IterT* base() const { return p_item_; }
        }; 

        typedef VectorIter<T> iterator;

        public:
            Vector() : start_(nullptr), finish_(nullptr), end_of_storage_(nullptr) {}
            Vector(int size) {
                start_ = iterator(new T[size]);
                end_of_storage_ = finish_ = iterator(start_.base() + size);
            }

            Vector(int size, const T &value) {
                start_ = iterator(new T[size]);
                end_of_storage_ = finish_ = iterator(start_.base() + size);

                iterator iter = start_;
                for(; iter != end(); ++iter) {
                    *iter = value;
                }
            }

            Vector(std::initializer_list<T> il) {
                size_t size = il.size();
                start_ = iterator(new T[size]);
                end_of_storage_ = finish_ = iterator(start_.base() + size);

                std::copy(il.begin(), il.end(), start_);
            }

            Vector(iterator first, iterator last) {
                size_t size = last - first;
                start_ = iterator(new T[size]);
                end_of_storage_ = finish_ = iterator(start_.base() + size);

                std::copy(first, last, start_);
            }
            
            Vector(const Vector &other) {
                size_t size = other.size();
                start_ = iterator(new T[size]);
                end_of_storage_ = finish_ = iterator(start_.base() + size);

                std::copy(other.begin(), other.end(), start_);
            }

            Vector(Vector &&other) {
                if (this == &other) {
                    return;
                }

                start_ = other.start_;
                finish_ = other.finish_;
                end_of_storage_ = other.end_of_storage_;

                other.start_ = iterator(nullptr);
                other.finish_ = iterator(nullptr);
                other.end_of_storage_ = iterator(nullptr);
            }

            Vector& operator=(const Vector &other) {
                delete[]start_.base();

                size_t size = other.size();
                start_ = iterator(new T[size]);
                end_of_storage_ = finish_ = iterator(start_.base() + size);

                std::copy(other.begin(), other.end(), start_);
                return *this;
            }

            Vector& operator=(Vector &&other) {
                if (this == &other) {
                    return *this;
                }

                delete []start_.base();
                start_ = other.start_;
                finish_ = other.finish_;
                end_of_storage_ = other.end_of_storage_;

                other.start_ = iterator(nullptr);
                other.finish_ = iterator(nullptr);
                other.end_of_storage_ = iterator(nullptr);

                return *this;                
            }

            Vector& operator=(std::initializer_list<T> il) {
                assert(il.size() > 0);
                
                delete []start_.base();

                size_t size = il.size();
                start_ = iterator(new T[size]);
                end_of_storage_ = finish_ = iterator(start_.base() + size);

                std::copy(il.begin(), il.end(), start_);
                return *this;
            }

            ~Vector() {
                delete []start_.base();
            }

            iterator begin() { return start_; }
            iterator end() { return finish_; }
            const iterator begin() const { return start_; }
            const iterator end() const { return finish_; }

            size_t size() const { return size_t(end() - begin()); }
            size_t capacity() const { return size_t(end_of_storage_ - begin()); }
            bool empty() const  { return begin() == end(); }

            T& operator[](int off) { return *(begin() + off); }
            const T& operator[](int off) const { return *(begin() + off); }

            T& front() { return *(begin()); }
            const T& front() const { return *(begin()); }

            T& back() { return *(--end()); }
            const T& back() const { return *(end() - 1); }

            T* data() { return begin().base(); }
            const T* data() const { return begin().base(); } 

            T& at(size_t n) {
                assert(n < size());
                return *(begin() + n);
            }

            const T& at(size_t n) const {
                assert(n < size());
                return *(begin() + n);
            }

            void push_back(const T &value) {
                if (capacity() == 0) {
                    start_ = iterator(new T[1]);
                    end_of_storage_ = finish_ = iterator(start_.base() + 1);
                    *start_ = value;
                    return;
                }

                if (finish_ == end_of_storage_) {
                    iterator old_begin_iter = begin();
                    iterator old_end_iter = end();
                    size_t old_capacity = capacity();

                    start_ = iterator(new T[2*old_capacity]);
                    std::copy(old_begin_iter, old_end_iter, start_);

                    end_of_storage_ = iterator(start_.base() + 2*old_capacity);
                    finish_ = iterator(start_.base() + (old_end_iter - old_begin_iter));

                    *finish_ = value;
                    ++finish_;

                    return;
                }

                *finish_ = value;
                ++finish_;
            }

            void push_back(T &&value) {
                if (capacity() == 0) {
                    start_ = iterator(new T[1]);
                    end_of_storage_ = finish_ = iterator(start_.base() + 1);
                    *start_ = value;
                    return;
                }

                if (finish_ == end_of_storage_) {
                    iterator old_begin_iter = begin();
                    iterator old_end_iter = end();
                    size_t old_capacity = capacity();

                    start_ = iterator(new T[2*old_capacity]);
                    std::copy(old_begin_iter, old_end_iter, start_);

                    end_of_storage_ = iterator(start_.base() + 2*old_capacity);
                    finish_ = iterator(start_.base() + (old_end_iter - old_begin_iter));

                    *finish_ = value;
                    ++finish_;

                    return;
                }

                *finish_ = value;
                ++finish_;
            }

            void pop_back() {
                --finish_;
                destory(finish_);
            }

            // 对容器进行扩容
            // 如果 n <= capacity，则不做任何处理；
            // 如果 n > capacity，则进行扩容，需要重新分配内存
            void reserve(size_t n) {
                if (n <= capacity()) {
                    return;
                }

                iterator old_begin_iter = begin();
                iterator old_end_iter = end();

                start_ = iterator(new T[n]);
                finish_ = iterator(start_.base() + (old_end_iter - old_begin_iter));
                end_of_storage_ = iterator(start_.base() + n);

                std::copy(old_begin_iter, old_end_iter, start_);            
            }


            void print() const {
                std::cout << "Vector: size = " << size() << ", capacity = " <<
                    capacity() << " [";
                for (auto iter = begin(); iter != end()-1; ++iter) {
                    std::cout << *iter << ", ";
                }                 
                std::cout << *(end()-1) << "]" << std::endl;
            }

        private:
            void destory(iterator iter) {
                iter->~T();
            }

        private:
            iterator start_;
            iterator finish_;
            iterator end_of_storage_;
    };

}

#endif // SDS_VECTOR_H
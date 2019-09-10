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
            VectorIter(const self &other) : p_item_(other.p_item_) {}

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
                start_ = iterator(new T[size]{0});
                end_of_storage_ = finish_ = iterator(start_.base() + size);
            }

            Vector(std::initializer_list<T> il) {
                size_t size = il.size();
                start_ = iterator(new T[size]{0});
                end_of_storage_ = finish_ = iterator(start_.base() + size);

                std::copy(il.begin(), il.end(), start_);
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

            void print() const {
                std::cout << "Vector: size = " << size() << ", capacity = " <<
                    capacity() << " [";
                for (auto iter = begin(); iter != end()-1; ++iter) {
                    std::cout << *iter << ", ";
                }                 
                std::cout << *(end()-1) << "]" << std::endl;
            }

        private:
            iterator start_;
            iterator finish_;
            iterator end_of_storage_;
    };

}

#endif // SDS_VECTOR_H
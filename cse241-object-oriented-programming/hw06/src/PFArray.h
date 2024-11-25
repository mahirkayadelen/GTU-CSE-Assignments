#include <memory>
#include <stdexcept>
#include <cstddef>
#include<iostream>
#include <algorithm>

using namespace std;   
    
    
template<class T>
class PFArray{
    public:
        using const_iterator = const T*;
        class Iterator{
            public:
                using value_type = T;
                using reference = T&;
                using pointer = T*;
                using difference_type = std::ptrdiff_t;
                using iterator_category = std::random_access_iterator_tag;

                Iterator(T* data) : data_(data) {}


                Iterator operator-(std::ptrdiff_t n) const;
                Iterator operator+(std::ptrdiff_t n) const;
                Iterator& operator--();
                friend Iterator operator+(std::ptrdiff_t n, const Iterator& it) { return Iterator(n + it.data_); }
                std::ptrdiff_t operator-(const Iterator& other) const;
                T& operator*() const;
                Iterator& operator++();
                Iterator& operator+=(difference_type n);
                Iterator& operator-=(difference_type n);

                bool operator!=(const Iterator& other) const;
                bool operator==(const Iterator& other) const;
                bool operator<(const Iterator& other) const;

                bool operator>=(const Iterator& other) const;
            private:
                T* data_;
        };
        
        Iterator begin();
        Iterator end();
        const_iterator cbegin() const;
        const_iterator cend() const;

        PFArray() : data_(nullptr), size_(0), capacity_(0) {}


        bool empty() const;
        int size() const;
        void clear();

        void push_back(T&& value);

        void erase(Iterator it) {
            if (it < begin() || it >= end()) {
                throw std::out_of_range("Invalid iterator");
            }

            for (auto i = it; i < end() - 1; ++i) {
                *i = *(i + 1);
            }
            --size_;
        }




    private:
        shared_ptr<T> data_;
        int size_;
        int capacity_;
};

template<class T>
typename PFArray<T>::Iterator PFArray<T>::Iterator::operator-(std::ptrdiff_t n) const{
    return Iterator(data_ - n);
}

template<class T>
typename PFArray<T>::Iterator PFArray<T>::Iterator::operator+(std::ptrdiff_t n) const{
    return Iterator(data_ + n);
}

template<class T>
typename PFArray<T>::Iterator& PFArray<T>::Iterator::operator--(){
    --data_;
    return *this;
}
template<class T>
std::ptrdiff_t PFArray<T>::Iterator::operator-(const Iterator& other) const{
    return data_ - other.data_;
}
template<class T>
T& PFArray<T>::Iterator::operator*() const{
    return *data_;
}

template<class T>
typename PFArray<T>::Iterator& PFArray<T>::Iterator::operator++(){
    ++data_;
    return *this;
}

template<class T>
typename PFArray<T>::Iterator& PFArray<T>::Iterator::operator+=(difference_type n){
    data_ += n; return *this;
}

template<class T>
typename PFArray<T>::Iterator& PFArray<T>::Iterator::operator-=(difference_type n){
    data_ -= n; return *this;
}

template<class T>
bool PFArray<T>::Iterator::operator!=(const Iterator& other) const{
    return data_ != other.data_;
}
template<class T>
bool PFArray<T>::Iterator::operator==(const Iterator& other) const{
    return data_ == other.data_;
}

template<class T>
bool PFArray<T>::Iterator::operator<(const Iterator& other) const{
    return data_ < other.data_;
}
template<class T>
bool PFArray<T>::Iterator::operator>=(const Iterator& other) const{
    return data_ >= other.data_; 
}
template<class T>
typename PFArray<T>::Iterator PFArray<T>::begin(){
    return Iterator(data_.get());
}
template<class T>
typename PFArray<T>::const_iterator PFArray<T>::cbegin() const{
    return data_.get();
}

template<class T>
typename PFArray<T>::const_iterator PFArray<T>::cend() const{
    return data_.get() + size_;
}
template<class T>
typename PFArray<T>::Iterator PFArray<T>::end(){
    return Iterator(data_.get() + size_);
}

template<class T>
bool PFArray<T>::empty() const{
    return size_ == 0;
}
template<class T>
int PFArray<T>::size() const{
    return size_;
}
template<class T>
void PFArray<T>::clear(){
    size_ = 0;
}
template<class T>
void PFArray<T>::push_back(T&& value){
    if (size_ == capacity_) {
        if (capacity_ == 0) {
            capacity_ = 1;
            }
            else{
                capacity_ *= 2;
            }
            auto new_data = make_shared<T>(capacity_);
            copy(begin(), end(), new_data.get());
            data_ = new_data;
        }
    data_.get()[size_++] = move(value);
}





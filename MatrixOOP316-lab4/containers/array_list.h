#pragma once
#include "base_list.h"

template<class T>
class ArrayList : public BaseList<T> {
public:
    ArrayList(size_t cap = 4) : BaseList<T>(cap) {}

    void remove(int index) override {
        if (index < 0 || static_cast<size_t>(index) >= this->_size)
            throw std::out_of_range("index out of range");

        this->_arr[index].~T();
        for (size_t i = index; i < this->_size - 1; ++i) {
            new (this->_arr + i) T(std::move(this->_arr[i + 1]));
            this->_arr[i + 1].~T();
        }
        --this->_size;
    }

    T& operator[](int index) {
        if (index < 0 || static_cast<size_t>(index) >= this->_size)
            throw std::out_of_range("index out of range");
        return this->_arr[index];
    }
};

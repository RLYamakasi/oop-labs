#pragma once
#include <stdexcept>
#include <cstddef>
#include <utility>
#include <new>
#include "IList.h"

template<class T>
class BaseList : public IList<T> {
protected:
    size_t _size;
    size_t _capacity;
    T* _arr;

    void _resize() {
        if (_size == _capacity) {
            _capacity = _capacity ? _capacity * 2 : 4;
            T* newArr = static_cast<T*>(operator new[](sizeof(T) * _capacity));
            for (size_t i = 0; i < _size; ++i) {
                new (newArr + i) T(std::move(_arr[i]));
                _arr[i].~T();
            }
            operator delete[](_arr);
            _arr = newArr;
        }
    }

public:
    BaseList(size_t cap = 4) : _size(0), _capacity(cap) {
        if (_capacity == 0) _capacity = 4;
        _arr = static_cast<T*>(operator new[](sizeof(T) * _capacity));
    }

    virtual ~BaseList() {
        for (size_t i = 0; i < _size; ++i) _arr[i].~T();
        operator delete[](_arr);
    }

    // IList<T> overrides
    size_t size() const override { return _size; }
    bool empty() const override { return _size == 0; }

    void push_back(T&& val)  { emplace_back(std::move(val)); }

    void push_front(T&& val)  { insert(0, std::move(val)); }

    void pop_back() override { remove(_size - 1); }
    void pop_front() override { remove(0); }

    T& front() override { return _arr[0]; }
    T& back() override { return _arr[_size - 1]; }

    virtual void remove(int index) = 0;

    template<typename... Args>
    void emplace_back(Args&&... args) {
        _resize();
        new (_arr + _size) T(std::forward<Args>(args)...);
        ++_size;
    }

    template<typename U>
    void insert(int index, U&& val) {
        if (index < 0 || static_cast<size_t>(index) > _size)
            throw std::out_of_range("index out of range");

        _resize();
        for (size_t i = _size; i > static_cast<size_t>(index); --i) {
            new (_arr + i) T(std::move(_arr[i - 1]));
            _arr[i - 1].~T();
        }
        new (_arr + index) T(std::forward<U>(val));
        ++_size;
    }

    T* begin() { return _arr; }
    T* end() { return _arr + _size; }
};

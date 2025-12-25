#pragma once
#include <cstddef>

template<typename T>
class IList {
public:
    virtual ~IList() = default;

    virtual size_t size() const = 0;
    virtual bool empty() const = 0;

    virtual T& front() = 0;
    virtual T& back() = 0;

    virtual void pop_front() = 0;
    virtual void pop_back() = 0;
};

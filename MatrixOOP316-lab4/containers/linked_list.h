#pragma once
#include "IList.h"
#include <cstddef>
#include <utility>
#include <stdexcept>

template<typename T>
class LinkedList : public IList<T> {
private:
    struct Node {
        T value;
        Node* next = nullptr;
        Node* prev = nullptr;

        template<typename U>
        explicit Node(U&& v) : value(std::forward<U>(v)), next(nullptr), prev(nullptr) {}
    };

    Node* head = nullptr;
    Node* tail = nullptr;
    size_t _size = 0;

    template<typename U>
    void emplace_back_impl(U&& val) {
        Node* n = new Node(std::forward<U>(val));
        if (!tail) head = tail = n;
        else {
            tail->next = n;
            n->prev = tail;
            tail = n;
        }
        ++_size;
    }

    template<typename U>
    void emplace_front_impl(U&& val) {
        Node* n = new Node(std::forward<U>(val));
        if (!head) head = tail = n;
        else {
            n->next = head;
            head->prev = n;
            head = n;
        }
        ++_size;
    }

public:
    LinkedList() = default;

    LinkedList(const LinkedList&) = delete;
    LinkedList& operator=(const LinkedList&) = delete;

    LinkedList(LinkedList&& other) noexcept
        : head(other.head), tail(other.tail), _size(other._size)
    {
        other.head = other.tail = nullptr;
        other._size = 0;
    }

    LinkedList& operator=(LinkedList&& other) noexcept {
        if (this != &other) {
            clear();
            head = other.head;
            tail = other.tail;
            _size = other._size;
            other.head = other.tail = nullptr;
            other._size = 0;
        }
        return *this;
    }

    ~LinkedList() { clear(); }

    void clear() {
        Node* cur = head;
        while (cur) {
            Node* nxt = cur->next;
            delete cur;
            cur = nxt;
        }
        head = tail = nullptr;
        _size = 0;
    }

    size_t size() const override { return _size; }
    bool empty() const override { return _size == 0; }

    void pop_back() override {
        if (!tail) return;
        Node* tmp = tail;
        tail = tail->prev;
        if (tail) tail->next = nullptr;
        else head = nullptr;
        delete tmp;
        --_size;
    }

    void pop_front() override {
        if (!head) return;
        Node* tmp = head;
        head = head->next;
        if (head) head->prev = nullptr;
        else tail = nullptr;
        delete tmp;
        --_size;
    }

    T& front() override {
        if (!head) throw std::out_of_range("front on empty list");
        return head->value;
    }
    T& back() override {
        if (!tail) throw std::out_of_range("back on empty list");
        return tail->value;
    }

    template<typename U>
    void push_back(U&& val) { emplace_back_impl(std::forward<U>(val)); }

    template<typename U>
    void push_front(U&& val) { emplace_front_impl(std::forward<U>(val)); }


    // ------------------------------------- iterator ----------------------------------
    class iterator {
        Node* ptr;
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type        = T;
        using difference_type   = std::ptrdiff_t;
        using pointer           = T*;
        using reference         = T&;

        iterator(Node* p = nullptr) : ptr(p) {}

        reference operator*() const { return ptr->value; }
        pointer operator->() const { return &ptr->value; }

        iterator& operator++() {   
            if (ptr) ptr = ptr->next;
            return *this;
        }

        iterator operator++(int) {
            iterator tmp(*this);
            ++(*this);
            return tmp;
        }


        bool operator==(const iterator& other) const { return ptr == other.ptr; }
        bool operator!=(const iterator& other) const { return ptr != other.ptr; }

        friend class LinkedList;
    };


    iterator begin() {return iterator(head);}
    iterator end() { return iterator(nullptr); }

    iterator erase(iterator it) {
        Node* n = it.ptr;
        if (!n) return end();

        Node* next = n->next;

        if (n->prev) n->prev->next = n->next;
        else head = n->next;

        if (n->next) n->next->prev = n->prev;
        else tail = n->prev;

        delete n;
        --_size;

        return iterator(next);
    }
    

};

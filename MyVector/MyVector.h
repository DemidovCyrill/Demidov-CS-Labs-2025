#ifndef MYVECTOR_H
#define MYVECTOR_H

#include <iostream>
#include <algorithm>

template <typename T>
class MyVector {
protected:
    T* pdata;
    size_t size;
    size_t max_size;

    void resize(size_t new_size);

public:
    MyVector(size_t initial_size = 1);
    MyVector(const MyVector& other);
    ~MyVector();
    MyVector& operator=(const MyVector& other);

    void add_element(const T& element);
    void delete_element(size_t index);
    int find(const T& element) const;

    T& operator[](size_t index);
    const T& operator[](size_t index) const;

    size_t get_size() const { return size; }
    size_t get_max_size() const { return max_size; }

    void sort();
};

// #include "MyVector.cpp"

#endif // MYVECTOR_H

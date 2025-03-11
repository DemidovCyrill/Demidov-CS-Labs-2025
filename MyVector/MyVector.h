#ifndef MYVECTOR_H
#define MYVECTOR_H

#include <iostream>
#include <algorithm>  // Для std::sort, std::copy

template <typename T>
class MyVector {
protected:
    T* pdata;       // Указатель на динамический массив
    size_t size;    // Количество элементов в векторе
    size_t max_size; // Максимальный размер вектора

    void resize(size_t new_size) {
        if (new_size < 1) new_size = 1;
        T* new_data = new T[new_size];
        std::copy(pdata, pdata + size, new_data);
        delete[] pdata;
        pdata = new_data;
        max_size = new_size;
    }

public:
    MyVector(size_t initial_size = 1)
        : size(0), max_size(initial_size) {
        pdata = new T[max_size];
    }

    MyVector(const MyVector& other)
        : size(other.size), max_size(other.max_size) {
        pdata = new T[max_size];
        std::copy(other.pdata, other.pdata + size, pdata);
    }

    ~MyVector() {
        delete[] pdata;
    }

    MyVector& operator=(const MyVector& other) {
        if (this == &other) return *this;
        delete[] pdata;
        size = other.size;
        max_size = other.max_size;
        pdata = new T[max_size];
        std::copy(other.pdata, other.pdata + size, pdata);
        return *this;
    }

    void add_element(const T& element) {
        if (size >= max_size) resize(max_size * 2);
        pdata[size++] = element;
    }

    void delete_element(size_t index) {
        if (index >= size) return;
        for (size_t i = index; i < size - 1; ++i) {
            pdata[i] = pdata[i + 1];
        }
        size--;
        if (size < max_size / 4 && max_size > 1) resize(max_size / 2);
    }

    int find(const T& element) const {
        for (size_t i = 0; i < size; ++i) {
            if (pdata[i] == element) return i;
        }
        return -1;
    }

    T& operator[](size_t index) {
        return pdata[index];
    }

    const T& operator[](size_t index) const {
        return pdata[index];
    }

    size_t get_size() const { return size; }
    size_t get_max_size() const { return max_size; }

    void sort() {
        std::sort(pdata, pdata + size);
    }
};

#endif // MYVECTOR_H

#include "MyVector.h"

template <typename T>
void MyVector <T>::resize(size_t new_size) {
    if (new_size < 1) new_size = 1;
    T* new_data = new T[new_size];
    std::copy(pdata, pdata + std::min(size, new_size), new_data);
    delete[] pdata;
    pdata = new_data;
    max_size = new_size;
}

template <typename T>
MyVector<T>::MyVector(size_t initial_size)
    : size(0), max_size(initial_size) {
    pdata = new T[max_size];
}

template <typename T>
MyVector<T>::MyVector(const MyVector& other)
    : size(other.size), max_size(other.max_size) {
    pdata = new T[max_size];
    std::copy(other.pdata, other.pdata + size, pdata);
}

template <typename T>
MyVector<T>::~MyVector() {
    delete[] pdata;
}

template <typename T>
MyVector<T>& MyVector<T>::operator=(const MyVector& other) {
    if (this == &other) return *this;
    delete[] pdata;
    size = other.size;
    max_size = other.max_size;
    pdata = new T[max_size];
    std::copy(other.pdata, other.pdata + size, pdata);
    return *this;
}

template <typename T>
void MyVector<T>::add_element(const T& element) {
    if (size >= max_size) resize(max_size * 2);
    pdata[size++] = element;
}

template <typename T>
void MyVector<T>::delete_element(size_t index) {
    if (index >= size) return;
    for (size_t i = index; i < size - 1; ++i) {
        pdata[i] = pdata[i + 1];
    }
    size--;
    if (size < max_size / 4 && max_size > 1) resize(max_size / 2);
}

template <typename T>
int MyVector<T>::find(const T& element) const {
    for (size_t i = 0; i < size; ++i) {
        if (pdata[i] == element) return i;
    }
    return -1;
}

template <typename T>
T& MyVector<T>::operator[](size_t index) {
    return pdata[index];
}

template <typename T>
const T& MyVector<T>::operator[](size_t index) const {
    return pdata[index];
}

template <typename T>
size_t MyVector<T>::get_size() const {
    return size;
}

template <typename T>
size_t MyVector<T>::get_max_size() const {
    return max_size;
}

template <typename T>
void MyVector<T>::sort() {
    std::sort(pdata, pdata + size);
}

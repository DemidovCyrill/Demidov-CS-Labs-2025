#ifndef MYSET_CPP
#define MYSET_CPP
#include "MySet.h"

template <typename T>
bool MySet<T>::is_element(const T& element) const {
    return q_find(element, 0, this -> size - 1) != -1;
}

template <typename T>
void MySet<T>::add_element(const T& element) {
    if (!is_element(element)) {
        MyVector<T>::add_element(element);
        this -> sort();
    }
}

template <typename T>
void MySet<T>::delete_element(const T& element) {
    int index = this -> find(element);
    if (index != -1) {
        MyVector<T>::delete_element(index);
    }
}

template <typename T>
MySet<T>& MySet<T>::operator+=(const MySet& other) {
    for (size_t i = 0; i < other.size; ++i) {
        add_element(other.pdata[i]);
    }
    return *this;
}

template <typename T>
MySet<T>& MySet<T>::operator-=(const MySet& other) {
    for (size_t i = 0; i < other.size; ++i) {
        delete_element(other.pdata[i]);
    }
    return *this;
}

template <typename T>
MySet<T>& MySet<T>::operator*=(const MySet& other) {
    for (size_t i = 0; i < this->size; ++i) {
        if (!other.is_element(this->pdata[i])) {
            delete_element(this->pdata[i]);
            --i;
        }
    }
    return *this;
}

template <typename T>
int MySet<T>::q_find(const T& element, int left, int right) const {
    if (left > right) return -1;
    int mid = left + (right - left) / 2;
    if (this->pdata[mid] == element) return mid;
    if (this->pdata[mid] > element) return q_find(element, left, mid - 1);
    return q_find(element, mid + 1, right);
}

#endif // MYSET_CPP

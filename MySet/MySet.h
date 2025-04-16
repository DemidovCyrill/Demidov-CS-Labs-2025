#ifndef MYSET_H
#define MYSET_H

#include "../MyVector/MyVector.h"
#include <algorithm>

template <typename T = char>
class MySet : public MyVector<T> {
private:
    int q_find(const T& element, int left, int right) const;

public:
    using MyVector<T>::MyVector;

    bool is_element(const T& element) const;
    void add_element(const T& element);
    void delete_element(const T& element);

    MySet& operator+=(const MySet& other);
    MySet& operator-=(const MySet& other);
    MySet& operator*=(const MySet& other);

    friend MySet operator+(const MySet& a, const MySet& b) {
        MySet result = a;
        result += b;
        return result;
    }

    friend MySet operator-(const MySet& a, const MySet& b) {
        MySet result = a;
        result -= b;
        return result;
    }

    friend MySet operator*(const MySet& a, const MySet& b) {
        MySet result;
        for (size_t i = 0; i < a.size; ++i) {
            if (b.is_element(a.pdata[i])) {
                result.add_element(a.pdata[i]);
            }
        }
        return result;
    }

    friend bool operator==(const MySet& a, const MySet& b) {
        if (a.size != b.size) return false;
        for (size_t i = 0; i < a.size; ++i) {
            if (!b.is_element(a.pdata[i])) return false;
        }
        return true;
    }
};

///////////////////////

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

std::ostream& operator<<(std::ostream& os, const MySet<int>& set) {
    bool first = false;
    std::cout << "\n{";
    for (size_t i = 0; i < set.get_size() - 1; ++i)
        std::cout << set[i] << ", ";
    std::cout << set[set.get_size()-1] << "}" << std::endl << std::endl;
    return os;
}

#endif

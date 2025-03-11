#ifndef MYSET_H
#define MYSET_H

#include "MyVector.h"
#include <algorithm>

template <typename T>
class MySet : public MyVector<T> {
public:
    using MyVector<T>::MyVector;  // Наследуем конструкторы

    bool is_element(const T& element) {
        return q_find(element, 0, this->size - 1) != -1;
    }

    void add_element(const T& element) {
        if (!is_element(element)) {
            MyVector<T>::add_element(element);
            this->sort();
        }
    }

    void delete_element(const T& element) {
        int index = this->find(element);
        if (index != -1) {
            MyVector<T>::delete_element(index);
        }
    }

    // Перегрузка операторов
    MySet& operator+=(const MySet& other) {
        for (size_t i = 0; i < other.size; ++i) {
            add_element(other.pdata[i]);
        }
        return *this;
    }

    MySet& operator-=(const MySet& other) {
        for (size_t i = 0; i < other.size; ++i) {
            delete_element(other.pdata[i]);
        }
        return *this;
    }

    MySet& operator*=(const MySet& other) {
        for (size_t i = 0; i < this->size; ++i) {
            if (!other.is_element(this->pdata[i])) {
                delete_element(this->pdata[i]);
                --i;  // Уменьшаем индекс, чтобы не пропустить элементы
            }
        }
        return *this;
    }

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
        MySet result = a;
        result *= b;
        return result;
    }

    friend bool operator==(const MySet& a, const MySet& b) {
        if (a.size != b.size) return false;
        for (size_t i = 0; i < a.size; ++i) {
            if (a.pdata[i] != b.pdata[i]) return false;
        }
        return true;
    }

private:
    int q_find(const T& element, int left, int right) const {
        if (left > right) return -1;
        int mid = left + (right - left) / 2;
        if (this->pdata[mid] == element) return mid;
        if (this->pdata[mid] > element) return q_find(element, left, mid - 1);
        return q_find(element, mid + 1, right);
    }
};

#endif // MYSET_H

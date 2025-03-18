#ifndef MYSET_H
#define MYSET_H

#include "../MyVector/MyVector.h"
#include <algorithm>

template <typename T>
class MySet : public MyVector<T> {
private:
    int q_find(const T& element, int left, int right) const;

public:
    using MyVector<T>::MyVector;  // Наследуем конструкторы

    bool is_element(const T& element) const;
    void add_element(const T& element);
    void delete_element(const T& element);

    // Перегрузка операторов
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
        // Правильная реализация пересечения множеств
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

// #include "MySet.сpp"

#endif // MYSET_H

#ifndef MYSET_H
#define MYSET_H

#include "../MyVector/MyVector.h"

class MySet : public MyVector<char*> {
public:
    MySet(size_t initial_size = 1) : MyVector<char*>(initial_size) {}
    MySet(const char* str) : MyVector<char*>(str) {}
    MySet(const MySet& other) : MyVector<char*>(other) {}

    bool is_element(const char* element) const {
        return find(element) != -1;
    }

    void add_element(const char* element) {
        if (!is_element(element)) {
            MyVector<char*>::add_element(element);
            // sort();
        }
    }

    void delete_element(const char* element) {
        int index = find(element);
        if (index != -1) {
            MyVector<char*>::delete_element(index);
        }
    }

    MySet& operator+=(const MySet& other) {
        for (size_t i = 0; i < other.get_size(); ++i) {
            add_element(other[i]);
        }
        return *this;
    }

    MySet& operator-=(const MySet& other) {
        for (size_t i = 0; i < other.get_size(); ++i) {
            delete_element(other[i]);
        }
        return *this;
    }

    MySet& operator*=(const MySet& other) {
        for (size_t i = 0; i < get_size(); ) {
            if (!other.is_element((*this)[i])) {
                delete_element((*this)[i]);
            } else {
                ++i;
            }
        }
        return *this;
    }
};

inline MySet operator+(const MySet& a, const MySet& b) {
    MySet result = a;
    result += b;
    return result;
}

inline MySet operator-(const MySet& a, const MySet& b) {
    MySet result = a;
    result -= b;
    return result;
}

inline MySet operator*(const MySet& a, const MySet& b) {
    MySet result;
    for (size_t i = 0; i < a.get_size(); ++i) {
        if (b.is_element(a[i])) {
            result.add_element(a[i]);
        }
    }
    return result;
}

inline bool operator==(const MySet& a, const MySet& b) {
    if (a.get_size() != b.get_size()) return false;
    for (size_t i = 0; i < a.get_size(); ++i) {
        if (!b.is_element(a[i])) return false;
    }
    return true;
}

inline std::ostream& operator<<(std::ostream& os, const MySet& set) {
    os << "{";
    for (size_t i = 0; i < set.get_size(); ++i) {
        if (i > 0) os << ", ";
        os << "\"" << set[i] << "\"";
    }
    return os << "}";
}

#endif // MYSET_H

#include "MySet.h"

MySet::MySet(size_t initial_size) : MyVector<char*>(initial_size) {}

MySet::MySet(char* str) : MyVector<char*>(str) {}

MySet::MySet(const MySet& other) : MyVector<char*>(other) {}

bool MySet::is_element(char* element) const {
    return find(element) != -1;
}

void MySet::add_element(char* element) {
    if (!is_element(element)) {
        MyVector<char*>::add_element(element);
        for (size_t i = 0; i < size - 1; i++) {
            for (size_t ii = 0; ii < size - i - 1; ii++) {
                if (char_utils::strcmp(pdata[ii], pdata[ii + 1]) > 0) {
                    char* temp = pdata[ii];
                    pdata[ii] = pdata[ii + 1];
                    pdata[ii + 1] = temp;
                }
            }
        }
    }
}

void MySet::insert_at(size_t index, char* element) {
    if (!is_element(element)) {
        MyVector<char*>::insert_at(index, element);
        for (size_t i = 0; i < size - 1; i++) {
            for (size_t ii = 0; ii < size - i - 1; ii++) {
                if (char_utils::strcmp(pdata[ii], pdata[ii + 1]) > 0) {
                    char* temp = pdata[ii];
                    pdata[ii] = pdata[ii + 1];
                    pdata[ii + 1] = temp;
                }
            }
        }
    }
}

void MySet::delete_element(char* element) {
    int index = find(element);
    if (index != -1) {
        MyVector<char*>::delete_element(index);
    }
}

template <typename Func>
void MySet::apply_from(const MySet& other, Func func) {
    for (size_t i = 0; i < other.get_size(); ++i) {
        func((char*)other[i]);
    }
}

MySet& MySet::operator+=(const MySet& other) {
    apply_from(other, [this](char* el) { add_element(el); });
    return *this;
}

MySet& MySet::operator-=(const MySet& other) {
    apply_from(other, [this](char* el) { delete_element(el); });
    return *this;
}

MySet& MySet::operator*=(const MySet& other) {
    for (size_t i = 0; i < get_size(); ) {
        if (!other.is_element((*this)[i])) {
            delete_element((*this)[i]);
        } else {
            ++i;
        }
    }
    return *this;
}

MySet operator+(const MySet& a, const MySet& b) {
    MySet result = a;
    result += b;
    return result;
}

MySet operator-(const MySet& a, const MySet& b) {
    MySet result = a;
    result -= b;
    return result;
}

MySet operator*(const MySet& a, const MySet& b) {
    MySet result;
    for (size_t i = 0; i < a.get_size(); ++i) {
        if (b.is_element((char*)a[i])) {
            result.add_element((char*)a[i]);
        }
    }
    return result;
}

bool operator==(const MySet& a, const MySet& b) {
    if (a.get_size() != b.get_size()) return false;
    for (size_t i = 0; i < a.get_size(); ++i) {
        if (!b.is_element((char*)a[i])) return false;
    }
    return true;
}

std::ostream& operator<<(std::ostream& os, const MySet& set) {
    return os << static_cast<const MyVector<char*>&>(set);
}

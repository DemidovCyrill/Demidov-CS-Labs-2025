#ifndef MYVECTOR_H
#define MYVECTOR_H

#include <iostream>
#include <stdexcept>

namespace char_utils {
    size_t strlen(char* str);
    char* copy_cstr(char* src);
    void delete_cstr(char* str);
    bool equal_cstr(char* a, char* b);
    int strcmp(char* a, char* b);
    bool less_cstr(char* a, char* b);
}

namespace char_utils {
    size_t strlen(char* str) {
        if (!str) return 0;
        size_t len = 0;
        while (str[len]) len++;
        return len;
    }

    char* copy_cstr(char* src) {
        if (!src) return nullptr;
        char* dst = new char[strlen(src) + 1];
        size_t i = 0;
        while (src[i]) {
            dst[i] = src[i];
            i++;
        }
        dst[i] = '\0';
        return dst;
    }

    void delete_cstr(char* str) {
        delete[] str;
    }

    bool equal_cstr(char* a, char* b) {
        if (!a && !b) return true;
        if (!a || !b) return false;
        size_t i = 0;
        while (a[i] && b[i] && a[i] == b[i]) i++;
        return a[i] == b[i];
    }

    int strcmp(char* a, char* b) {
        if (!a && !b) return 0;
        if (!a) return -1;
        if (!b) return 1;

        size_t i = 0;
        while (a[i] && b[i]) {
            if (a[i] < b[i]) return -1;
            if (a[i] > b[i]) return 1;
            i++;
        }

        if (!a[i] && !b[i]) return 0;
        if (!a[i]) return -1;
        return 1;
    }

    bool less_cstr(char* a, char* b) {
        return strcmp(a, b) < 0;
    }
}

#define MAX_SIZE 100

template <typename T = int>
class MyVector {
protected:
    T* pdata;
    size_t size;
    size_t max_size;

    void resize(size_t new_size);

public:
    MyVector(size_t initial_size = 1);
    MyVector(const T& first_element);
    MyVector(const MyVector& other);
    virtual ~MyVector();

    MyVector& operator=(const MyVector& other);
    virtual void add_element(const T& element);
    void delete_element(size_t index);
    void insert_at(size_t index, const T& element);
    int find(const T& element) const;

    T& operator[](size_t index);
    const T& operator[](size_t index) const;

    void sort();

    size_t get_size() const;
    size_t get_max_size() const;
};



template <typename T>
std::ostream& operator<<(std::ostream& os, const MyVector<T>& vec);




template <typename T>
MyVector<T>::MyVector(size_t initial_size) : size(0), max_size(initial_size) {
    pdata = new T[max_size];
}

template <typename T>
MyVector<T>::MyVector(const T& first_element) : size(1), max_size(1) {
    pdata = new T[1];
    pdata[0] = first_element;
}

template <typename T>
MyVector<T>::MyVector(const MyVector& other) : size(other.size), max_size(other.max_size) {
    pdata = new T[max_size];
    for (size_t i = 0; i < size; i++) {
        pdata[i] = other.pdata[i];
    }
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
    for (size_t i = 0; i < size; i++) {
        pdata[i] = other.pdata[i];
    }
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
void MyVector<T>::insert_at(size_t index, const T& element) {
    if (index > size) {
        throw std::out_of_range("Index out of range");
    }

    if (size >= max_size) {
        resize(max_size * 2);
    }

    for (size_t i = size; i > index; --i) {
        pdata[i] = pdata[i - 1];
    }

    pdata[index] = element;
    size++;
}

template <typename T>
int MyVector<T>::find(const T& element) const {
    for (size_t i = 0; i < size; ++i) {
        if (pdata[i] == element) return i;
    }
    return -1;
}

// template <typename T>
// T& MyVector<T>::operator[](size_t index) {
//     if (index >= size) throw std::out_of_range("Index out of range");
//     return pdata[index];
// }

// template <typename T>
// const T& MyVector<T>::operator[](size_t index) const {
//     if (index >= size) throw std::out_of_range("Index out of range");
//     return pdata[index];
// }

template <typename T>
void MyVector<T>::sort() {
    for (size_t i = 0; i < size; i++) {
        int maxx = i;
        for (size_t ii = i; ii < size; ii++) {
            if (pdata[maxx] < pdata[ii]) {
                maxx = ii;
            }
        }
        T c = pdata[i];
        pdata[i] = pdata[maxx];
        pdata[maxx] = c;
    }
}

template <typename T>
size_t MyVector<T>::get_size() const {
    return size;
}

template <typename T>
size_t MyVector<T>::get_max_size() const {
    return max_size;
}

void MyVector<char*>::resize(size_t new_size) {
    if (new_size < 1) new_size = 1;
    char** new_data = new char*[new_size];
    for (size_t i = 0; i < size; i++) {
        new_data[i] = pdata[i];
    }
    delete[] pdata;
    pdata = new_data;
    max_size = new_size;
}

template <char*>
void clear() {
    for (size_t i = 0; i < size; ++i) {
        char_utils::delete_cstr(pdata[i]);
    }
    delete[] pdata;
}

template <char*>
void copy_from(const MyVector& other) {
    size = other.size;
    max_size = other.max_size;
    pdata = new char*[max_size];
    for (size_t i = 0; i < size; ++i) {
        pdata[i] = char_utils::copy_cstr(other.pdata[i]);
    }
}

MyVector<char*>::MyVector(size_t initial_size) : size(0), max_size(initial_size) {
    pdata = new char*[max_size];
}


// template <char*>
// ~MyVector() {
//     clear();
// }

// template <char*>
// MyVector<char*>& operator=(const MyVector& other) {
//     if (this == &other) return *this;
//     clear();
//     copy_from(other);
//     return *this;
// }

template <char*>
void dd_element(char* element) {
    if (size >= max_size) resize(max_size * 2);
    pdata[size++] = char_utils::copy_cstr(element);
}

template <char*>
void delete_element(size_t index) {
    if (index >= size) return;
    char_utils::delete_cstr(pdata[index]);
    for (size_t i = index; i < size - 1; ++i) {
        pdata[i] = pdata[i + 1];
    }
    size--;
    if (size < max_size / 4 && max_size > 1) resize(max_size / 2);
}

template <char*>
void insert_at(size_t index, char* element) {
    if (index > size) {
        throw std::out_of_range("Index out of range");
    }

    if (size >= max_size) {
        resize(max_size * 2);
    }

    for (size_t i = size; i > index; --i) {
        pdata[i] = pdata[i - 1];
    }

    pdata[index] = char_utils::copy_cstr(element);
    size++;
}

template <char*>
int find(char* element) {
    for (size_t i = 0; i < size; ++i) {
        if (char_utils::equal_cstr(pdata[i], element)) return i;
    }
    return -1;
}

void MyVector<char*>::sort() {
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



template <typename T>
std::ostream& operator<<(std::ostream& os, const MyVector<T>& vec) {
    os << "\n{";
    for (size_t i = 0; i < vec.get_size(); ++i) {
        if (i > 0) os << ", ";
        os << vec[i];
    }
    return os << "}\n";
}


#endif // MYVECTOR_H

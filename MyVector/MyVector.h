#ifndef MYVECTOR_H
#define MYVECTOR_H

#include <iostream>
#include <algorithm>
#include <cstring>

template <typename T = int>
class MyVector {
protected:
    T* pdata;
    size_t size;
    size_t max_size;

    void resize(size_t new_size) {
        if(new_size < 1) new_size = 1;
        T* new_data = new T[new_size];
        std::copy(pdata, pdata + size, new_data);
        delete[] pdata;
        pdata = new_data;
        max_size = new_size;
    }

public:
    MyVector(size_t initial_size = 1) : size(0), max_size(initial_size) {
        pdata = new T[max_size];
    }

    MyVector(const T& first_element) : size(1), max_size(1) {
        pdata = new T[1];
        pdata[0] = first_element;
    }

    MyVector(const MyVector& other) : size(other.size), max_size(other.max_size) {
        pdata = new T[max_size];
        std::copy(other.pdata, other.pdata + size, pdata);
    }

    virtual ~MyVector() {
        delete[] pdata;
    }

    MyVector& operator=(const MyVector& other) {
        if(this == &other) return *this;
        delete[] pdata;
        size = other.size;
        max_size = other.max_size;
        pdata = new T[max_size];
        std::copy(other.pdata, other.pdata + size, pdata);
        return *this;
    }

    virtual void add_element(const T& element) {
        if(size >= max_size) resize(max_size * 2);
        pdata[size++] = element;
    }

    void delete_element(size_t index) {
        if(index >= size) return;
        for(size_t i = index; i < size - 1; ++i) {
            pdata[i] = pdata[i + 1];
        }
        size--;
        if(size < max_size / 4 && max_size > 1) resize(max_size / 2);
    }

    int find(const T& element) const {
        for(size_t i = 0; i < size; ++i) {
            if(pdata[i] == element) return i;
        }
        return -1;
    }

    T& operator[](size_t index) {
        if(index >= size) throw std::out_of_range("Index out of range");
        return pdata[index];
    }

    const T& operator[](size_t index) const {
        if(index >= size) throw std::out_of_range("Index out of range");
        return pdata[index];
    }

    void sort() {
        std::sort(pdata, pdata + size);
    }

    size_t get_size() const { return size; }
    size_t get_max_size() const { return max_size; }
};

template<>
void MyVector<int>::add_element(const int& element) {
    if(size >= max_size) resize(max_size * 2);
    pdata[size++] = element;
}

template<>
class MyVector<char*> {
protected:
    char** pdata;
    size_t size;
    size_t max_size;

    void resize(size_t new_size) {
        if(new_size < 1) new_size = 1;
        char** new_data = new char*[new_size];
        std::copy(pdata, pdata + size, new_data);
        delete[] pdata;
        pdata = new_data;
        max_size = new_size;
    }

public:
    MyVector(const char* str) : size(1), max_size(1) {
        pdata = new char*[1];
        pdata[0] = new char[strlen(str) + 1];
        strcpy(pdata[0], str);
    }

    MyVector(size_t initial_size = 1) : size(0), max_size(initial_size) {
        pdata = new char*[max_size];
    }

    MyVector(const MyVector& other) : size(other.size), max_size(other.max_size) {
        pdata = new char*[max_size];
        for(size_t i = 0; i < size; ++i) {
            pdata[i] = new char[strlen(other.pdata[i]) + 1];
            strcpy(pdata[i], other.pdata[i]);
        }
    }

    ~MyVector() {
        for(size_t i = 0; i < size; ++i) {
            delete[] pdata[i];
        }
        delete[] pdata;
    }

    MyVector& operator=(const MyVector& other) {
        if(this == &other) return *this;

        for(size_t i = 0; i < size; ++i) {
            delete[] pdata[i];
        }
        delete[] pdata;

        size = other.size;
        max_size = other.max_size;
        pdata = new char*[max_size];

        for(size_t i = 0; i < size; ++i) {
            pdata[i] = new char[strlen(other.pdata[i]) + 1];
            strcpy(pdata[i], other.pdata[i]);
        }

        return *this;
    }

    void add_element(const char* element) {
        if(size >= max_size) resize(max_size * 2);
        pdata[size] = new char[strlen(element) + 1];
        strcpy(pdata[size], element);
        size++;
    }

    void delete_element(size_t index) {
        if(index >= size) return;

        delete[] pdata[index];

        for(size_t i = index; i < size - 1; ++i) {
            pdata[i] = pdata[i + 1];
        }

        size--;
        if(size < max_size / 4 && max_size > 1) resize(max_size / 2);
    }

    int find(const char* element) const {
        for(size_t i = 0; i < size; ++i) {
            if(strcmp(pdata[i], element) == 0) return i;
        }
        return -1;
    }

    char* operator[](size_t index) {
        if(index >= size) throw std::out_of_range("Index out of range");
        return pdata[index];
    }

    const char* operator[](size_t index) const {
        if(index >= size) throw std::out_of_range("Index out of range");
        return pdata[index];
    }

    void sort() {
        std::sort(pdata, pdata + size, [](const char* a, const char* b) {
            return strcmp(a, b) < 0;
        });
    }

    size_t get_size() const { return size; }
    size_t get_max_size() const { return max_size; }
};

std::ostream& operator<<(std::ostream& os, const MyVector<int>& vec) {
    os << "\n{";
    for(size_t i = 0; i < vec.get_size(); ++i) {
        if(i > 0) os << ", ";
        os << vec[i];
    }
    return os << "}\n";
}

std::ostream& operator<<(std::ostream& os, const MyVector<char*>& vec) {
    os << "\n{";
    for(size_t i = 0; i < vec.get_size(); ++i) {
        if(i > 0) os << ", ";
        os << vec[i];
    }
    return os << "}\n";
}

#endif // MYVECTOR_H

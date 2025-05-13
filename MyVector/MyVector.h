#ifndef MYVECTOR_H
#define MYVECTOR_H
#include <iostream>
#include <algorithm>
#include "MyStack.h"

template <typename T = int>
class MyVector {
protected:
    MyStack<T> stack;
    size_t size;
    size_t max_size;

    T getAt(size_t index) const {
        if(index >= size) throw std::out_of_range("Index out of range");

        MyStack<T> tempStack = stack;

        for(size_t i = 0; i < size - index - 1; ++i) {
            tempStack.pop();
        }

        return tempStack.get();
    }

public:
    MyVector(size_t initial_size = 1) : size(0), max_size(initial_size) {}

    MyVector(const T& first_element) : size(1), max_size(1) {
        stack.append(first_element);
    }

    MyVector(const MyVector& other) : size(other.size), max_size(other.max_size) {
        MyStack<T> temp;
        MyStack<T> otherCopy = other.stack;

        while(!otherCopy.any()) {
            temp.append(otherCopy.get());
            otherCopy.pop();
        }

        while(!temp.any()) {
            stack.append(temp.get());
            temp.pop();
        }
    }

    virtual ~MyVector() {
        while(!stack.any()) {
            stack.pop();
        }
    }

    MyVector& operator=(const MyVector& other) {
        if(this == &other) return *this;

        while(!stack.any()) {
            stack.pop();
        }

        size = other.size;
        max_size = other.max_size;

        MyStack<T> temp;
        MyStack<T> otherCopy = other.stack;

        while(!otherCopy.any()) {
            temp.append(otherCopy.get());
            otherCopy.pop();
        }

        while(!temp.any()) {
            stack.append(temp.get());
            temp.pop();
        }

        return *this;
    }

    void insert_at(size_t index, const T& element) {
        if(index > size) throw std::out_of_range("Index out of range for insertion");

        MyStack<T> temp;
        size_t count = 0;

        while(!stack.any() && count < size - index) {
            temp.append(stack.get());
            stack.pop();
            count++;
        }

        temp.append(element);

        while(!stack.any()) {
            temp.append(stack.get());
            stack.pop();
        }

        while(!temp.any()) {
            stack.append(temp.get());
            temp.pop();
        }

        size++;
        if(size > max_size) max_size = size;
    }

    virtual void add_element(const T& element) {
        MyStack<T> temp;

        while(!stack.any()) {
            temp.append(stack.get());
            stack.pop();
        }

        stack.append(element);

        while(!temp.any()) {
            stack.append(temp.get());
            temp.pop();
        }

        size++;
        if(size > max_size) max_size = size;
    }

    void delete_element(size_t index) {
        if(index >= size) return;

        MyStack<T> temp;
        size_t current = 0;

        while(!stack.any()) {
            T value = stack.get();
            stack.pop();

            if(current != size - index - 1) {
                temp.append(value);
            }
            current++;
        }

        size--;

        while(!temp.any()) {
            stack.append(temp.get());
            temp.pop();
        }

        if(size < max_size / 4 && max_size > 1) max_size /= 2;
    }

    int find(const T& element) const {
        for(size_t i = 0; i < size; ++i) {
            if(getAt(i) == element) {
                return i;
            }
        }

        return -1;
    }

    class ElementProxy {
    private:
        MyVector& vector;
        size_t index;

    public:
        ElementProxy(MyVector& vec, size_t idx) : vector(vec), index(idx) {}

        ElementProxy& operator=(const T& value) {
            T* temp = new T[vector.size];

            for(size_t i = 0; i < vector.size; ++i) {
                temp[i] = vector.getAt(i);
            }

            temp[index] = value;

            while(!vector.stack.any()) {
                vector.stack.pop();
            }

            for(int i = vector.size - 1; i >= 0; --i) {
                vector.stack.append(temp[i]);
            }

            delete[] temp;

            return *this;
        }

        operator T() const {
            return vector.getAt(index);
        }
    };

    ElementProxy operator[](size_t index) {
        if(index >= size) throw std::out_of_range("Index out of range");
        return ElementProxy(*this, index);
    }

    const T operator[](size_t index) const {
        return getAt(index);
    }

    void sort() {
        T* temp = new T[size];

        for(size_t i = 0; i < size; ++i) {
            temp[i] = getAt(i);
        }

        std::sort(temp, temp + size);

        while(!stack.any()) {
            stack.pop();
        }

        for(int i = size - 1; i >= 0; --i) {
            stack.append(temp[i]);
        }

        delete[] temp;
    }

    size_t get_size() const { return size; }
    size_t get_max_size() const { return max_size; }
};

template<>
void MyVector<int>::add_element(const int& element) {
    MyStack<int> temp;

    while(!stack.any()) {
        temp.append(stack.get());
        stack.pop();
    }

    stack.append(element);

    while(!temp.any()) {
        stack.append(temp.get());
        temp.pop();
    }

    size++;
    if(size > max_size) max_size = size;
}

template<>
class MyVector<char*> {
protected:
    MyStack<char*> stack;
    size_t size;
    size_t max_size;

    size_t string_length(const char* str) const {
        size_t len = 0;
        while(str[len] != '\0') {
            len++;
        }
        return len;
    }

    void string_copy(char* dest, const char* src) {
        size_t i = 0;
        while(src[i] != '\0') {
            dest[i] = src[i];
            i++;
        }
        dest[i] = '\0';
    }

    int string_compare(const char* s1, const char* s2) const {
        while(*s1 && (*s1 == *s2)) {
            s1++;
            s2++;
        }
        return *(const unsigned char*)s1 - *(const unsigned char*)s2;
    }

    char* getAt(size_t index) const {
        if(index >= size) throw std::out_of_range("Index out of range");

        MyStack<char*> tempStack = stack;

        for(size_t i = 0; i < size - index - 1; ++i) {
            tempStack.pop();
        }

        return tempStack.get();
    }

public:
    MyVector(size_t initial_size = 1) : size(0), max_size(initial_size) {}

    MyVector(const char* str) : size(1), max_size(1) {
        char* copy = new char[string_length(str) + 1];
        string_copy(copy, str);
        stack.append(copy);
    }

    MyVector(const MyVector& other) : size(other.size), max_size(other.max_size) {
        MyStack<char*> temp;
        MyStack<char*> otherCopy = other.stack;

        while(!otherCopy.any()) {
            char* str = otherCopy.get();
            char* copy = new char[string_length(str) + 1];
            string_copy(copy, str);
            temp.append(copy);
            otherCopy.pop();
        }

        while(!temp.any()) {
            stack.append(temp.get());
            temp.pop();
        }
    }

    ~MyVector() {
        while(!stack.any()) {
            char* str = stack.get();
            delete[] str;
            stack.pop();
        }
    }

    void insert_at(size_t index, const char* element) {
        if(index > size) throw std::out_of_range("Index out of range for insertion");

        char* copy = new char[string_length(element) + 1];
        string_copy(copy, element);

        MyStack<char*> temp;
        size_t count = 0;

        while(!stack.any() && count < size - index) {
            temp.append(stack.get());
            stack.pop();
            count++;
        }

        temp.append(copy);

        while(!stack.any()) {
            temp.append(stack.get());
            stack.pop();
        }

        while(!temp.any()) {
            stack.append(temp.get());
            temp.pop();
        }

        size++;
        if(size > max_size) max_size = size;
    }

    MyVector& operator=(const MyVector& other) {
        if(this == &other) return *this;

        while(!stack.any()) {
            char* str = stack.get();
            delete[] str;
            stack.pop();
        }

        size = other.size;
        max_size = other.max_size;

        MyStack<char*> temp;
        MyStack<char*> otherCopy = other.stack;

        while(!otherCopy.any()) {
            char* str = otherCopy.get();
            char* copy = new char[string_length(str) + 1];
            string_copy(copy, str);
            temp.append(copy);
            otherCopy.pop();
        }

        while(!temp.any()) {
            stack.append(temp.get());
            temp.pop();
        }

        return *this;
    }

    void add_element(const char* element) {
        char* copy = new char[string_length(element) + 1];
        string_copy(copy, element);

        MyStack<char*> temp;

        while(!stack.any()) {
            temp.append(stack.get());
            stack.pop();
        }

        stack.append(copy);

        while(!temp.any()) {
            stack.append(temp.get());
            temp.pop();
        }

        size++;
        if(size > max_size) max_size = size;
    }

    void delete_element(size_t index) {
        if(index >= size) return;

        MyStack<char*> temp;
        size_t current = 0;

        while(!stack.any()) {
            char* value = stack.get();
            stack.pop();

            if(current != size - index - 1) {
                temp.append(value);
            } else {
                delete[] value;
            }
            current++;
        }

        size--;

        while(!temp.any()) {
            stack.append(temp.get());
            temp.pop();
        }

        if(size < max_size / 4 && max_size > 1) max_size /= 2;
    }

    int find(const char* element) const {
        for(size_t i = 0; i < size; ++i) {
            char* current = getAt(i);
            if(string_compare(current, element) == 0) {
                return i;
            }
        }

        return -1;
    }

    class ElementProxy {
    private:
        MyVector& vector;
        size_t index;

    public:
        ElementProxy(MyVector& vec, size_t idx) : vector(vec), index(idx) {}

        ElementProxy& operator=(const char* value) {
            char** temp = new char*[vector.size];

            for(size_t i = 0; i < vector.size; ++i) {
                char* str = vector.getAt(i);
                if(i == index) {
                    temp[i] = new char[vector.string_length(value) + 1];
                    vector.string_copy(temp[i], value);
                } else {
                    temp[i] = new char[vector.string_length(str) + 1];
                    vector.string_copy(temp[i], str);
                }
            }

            while(!vector.stack.any()) {
                char* str = vector.stack.get();
                delete[] str;
                vector.stack.pop();
            }

            for(int i = vector.size - 1; i >= 0; --i) {
                vector.stack.append(temp[i]);
            }

            delete[] temp;

            return *this;
        }

        operator char*() const {
            return vector.getAt(index);
        }
    };

    ElementProxy operator[](size_t index) {
        if(index >= size) throw std::out_of_range("Index out of range");
        return ElementProxy(*this, index);
    }

    const char* operator[](size_t index) const {
        return getAt(index);
    }

    void sort() {
        char** temp = new char*[size];

        for(size_t i = 0; i < size; ++i) {
            char* str = getAt(i);
            temp[i] = new char[string_length(str) + 1];
            string_copy(temp[i], str);
        }

        for(size_t i = 0; i < size - 1; ++i) {
            for(size_t j = 0; j < size - i - 1; ++j) {
                if(string_compare(temp[j], temp[j + 1]) > 0) {
                    char* tmp = temp[j];
                    temp[j] = temp[j + 1];
                    temp[j + 1] = tmp;
                }
            }
        }

        while(!stack.any()) {
            char* str = stack.get();
            delete[] str;
            stack.pop();
        }

        for(int i = size - 1; i >= 0; --i) {
            stack.append(temp[i]);
        }

        delete[] temp;
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

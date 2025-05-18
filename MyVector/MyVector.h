#ifndef MYVECTOR_H
#define MYVECTOR_H

#include <iostream>
#include <stdexcept>
#include <cstring> // Для strcmp и strcpy

namespace char_utils {
    inline size_t strlen(const char* str) {
        if (!str) return 0;
        size_t len = 0;
        while (str[len]) len++;
        return len;
    }

    inline char* copy_cstr(const char* src) {
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

    inline void delete_cstr(char* str) {
        delete[] str;
    }

    inline bool equal_cstr(const char* a, const char* b) {
        if (!a && !b) return true;
        if (!a || !b) return false;
        return std::strcmp(a, b) == 0;
    }

    inline int strcmp(const char* a, const char* b) {
        if (!a && !b) return 0;
        if (!a) return -1;
        if (!b) return 1;
        return std::strcmp(a, b);
    }
}

template <typename T = int>
class MyVector {
protected:
    T* pdata;
    size_t size;
    size_t max_size;

    void resize(size_t new_size) {
        if (new_size < 1) new_size = 1;
        T* new_data = new T[new_size];
        for (size_t i = 0; i < size; i++) {
            new_data[i] = pdata[i];
        }
        delete[] pdata;
        pdata = new_data;
        max_size = new_size;
    }

    void clear() {
        delete[] pdata;
        pdata = nullptr;
        size = 0;
        max_size = 0;
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
        for (size_t i = 0; i < size; i++) {
            pdata[i] = other.pdata[i];
        }
    }

    virtual ~MyVector() {
        clear();
    }

    MyVector& operator=(const MyVector& other) {
        if (this == &other) return *this;

        clear();

        size = other.size;
        max_size = other.max_size;
        pdata = new T[max_size];

        for (size_t i = 0; i < size; i++) {
            pdata[i] = other.pdata[i];
        }

        return *this;
    }

    virtual void add_element(const T& element) {
        if (size >= max_size) resize(max_size * 2);
        pdata[size++] = element;
    }

    void delete_element(size_t index) {
        if (index >= size) return;

        for (size_t i = index; i < size - 1; ++i) {
            pdata[i] = pdata[i + 1];
        }

        size--;
        if (size < max_size / 4 && max_size > 1) {
            resize(max_size / 2);
        }
    }

    void insert_at(size_t index, const T& element) {
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

    int find(const T& element) const {
        for (size_t i = 0; i < size; ++i) {
            if (pdata[i] == element) return i;
        }
        return -1;
    }

    T& operator[](size_t index) {
        if (index >= size) throw std::out_of_range("Index out of range");
        return pdata[index];
    }

    const T& operator[](size_t index) const {
        if (index >= size) throw std::out_of_range("Index out of range");
        return pdata[index];
    }

    void sort() {
        for (size_t i = 0; i < size; i++) {
            size_t max_idx = i;
            for (size_t j = i; j < size; j++) {
                if (pdata[max_idx] < pdata[j]) {
                    max_idx = j;
                }
            }
            std::swap(pdata[i], pdata[max_idx]);
        }
    }

    size_t get_size() const { return size; }
    size_t get_max_size() const { return max_size; }
};

// Специализация для char*
template <>
class MyVector<char*> {
protected:
    char** pdata;
    size_t size;
    size_t max_size;

    void resize(size_t new_size) {
        if (new_size < 1) new_size = 1;
        char** new_pdata = new char*[new_size]();
        for(size_t i = 0; i < size; ++i) {
            new_pdata[i] = pdata[i];
        }
        delete[] pdata;
        pdata = new_pdata;
        max_size = new_size;
    }

    int partition(char** array, int left, int right) {
        const char* pivot = array[(left + right) / 2];
        int i = left;
        int j = right;

        while(i <= j) {
            while(strcmp(array[i], pivot) < 0) ++i;
            while(strcmp(array[j], pivot) > 0) --j;
            if(i <= j) std::swap(array[i++], array[j--]);
        }
        return j;
    }

    void quickSort(char** array, int left, int right) {
        if(left < right) {
            int q = partition(array, left, right);
            quickSort(array, left, q);
            quickSort(array, q + 1, right);
        }
    }

public:
    MyVector(size_t initial_size = 1) : size(0), max_size(initial_size) {
        pdata = new char*[max_size]();
    }

    MyVector(const char* element) : size(1), max_size(1) {
        pdata = new char*[1];
        if(element) {
            pdata[0] = char_utils::copy_cstr(element);
        } else {
            pdata[0] = nullptr;
        }
    }

    MyVector(const MyVector& other) : size(other.size), max_size(other.max_size) {
        pdata = new char*[max_size]();
        for(size_t i = 0; i < size; ++i) {
            if(other.pdata[i]) {
                pdata[i] = char_utils::copy_cstr(other.pdata[i]);
            }
        }
    }

    ~MyVector() {
        for(size_t i = 0; i < size; ++i) {
            char_utils::delete_cstr(pdata[i]);
        }
        delete[] pdata;
    }

    void add_element(const char* element) {
        if(size == max_size) {
            resize(max_size ? max_size * 2 : 1);
        }
        pdata[size] = char_utils::copy_cstr(element);
        ++size;
    }

    void delete_element(size_t index) {
        if(index >= size) return;

        char_utils::delete_cstr(pdata[index]);
        for(size_t i = index; i < size - 1; ++i) {
            pdata[i] = pdata[i + 1];
        }
        --size;

        if(size < max_size / 4 && max_size > 1) {
            resize(max_size / 2);
        }
    }

    void insert_at(size_t index, const char* element) {
        if(index > size) {
            throw std::out_of_range("Index out of range");
        }

        if(size >= max_size) {
            resize(max_size * 2);
        }

        for(size_t i = size; i > index; --i) {
            pdata[i] = pdata[i - 1];
        }

        pdata[index] = char_utils::copy_cstr(element);
        size++;
    }

    int find(const char* element) const {
        if(element == nullptr) {
            for(size_t i = 0; i < size; ++i) {
                if(pdata[i] == nullptr) {
                    return static_cast<int>(i);
                }
            }
        } else {
            for(size_t i = 0; i < size; ++i) {
                if(pdata[i] && char_utils::equal_cstr(element, pdata[i])) {
                    return static_cast<int>(i);
                }
            }
        }
        return -1;
    }

    void sort() {
        if(size > 1) {
            quickSort(pdata, 0, static_cast<int>(size) - 1);
        }
    }

    char*& operator[](size_t index) {
        if(index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return pdata[index];
    }

    const char* operator[](size_t index) const {
        if(index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return pdata[index];
    }

    MyVector& operator=(const MyVector& other) {
        if(this != &other) {
            // Очистка текущих данных
            for(size_t i = 0; i < size; ++i) {
                char_utils::delete_cstr(pdata[i]);
            }
            delete[] pdata;

            // Копирование данных из other
            max_size = other.max_size;
            size = other.size;
            pdata = new char*[max_size]();

            for(size_t i = 0; i < size; ++i) {
                if(other.pdata[i]) {
                    pdata[i] = char_utils::copy_cstr(other.pdata[i]);
                }
            }
        }
        return *this;
    }

    size_t get_size() const { return size; }
    size_t get_max_size() const { return max_size; }
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const MyVector<T>& vec) {
    os << "\n{";
    for (size_t i = 0; i < vec.get_size(); ++i) {
        if (i > 0) os << ", ";
        os << vec[i];
    }
    return os << "}\n";
}

template <>
std::ostream& operator<<(std::ostream& os, const MyVector<char*>& vec) {
    os << "\n{";
    for (size_t i = 0; i < vec.get_size(); ++i) {
        if (i > 0) os << ", ";
        if(vec[i]) {
            os << "\"" << vec[i] << "\"";
        } else {
            os << "null";
        }
    }
    return os << "}\n";
}

#endif // MYVECTOR_H

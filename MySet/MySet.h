#ifndef MYSET_H
#define MYSET_H

#include "../MyVector/MyVector.h"

class MySet : public MyVector<char*> {
public:
    MySet(size_t initial_size = 1);
    MySet(char* str);
    MySet(const MySet& other);

    bool is_element(char* element) const;
    void add_element(char* element) override;
    void insert_at(size_t index, char* element);
    void delete_element(char* element);

    MySet& operator+=(const MySet& other);
    MySet& operator-=(const MySet& other);
    MySet& operator*=(const MySet& other);

private:
    template <typename Func>
    void apply_from(const MySet& other, Func func);
};

MySet operator+(const MySet& a, const MySet& b);
MySet operator-(const MySet& a, const MySet& b);
MySet operator*(const MySet& a, const MySet& b);
bool operator==(const MySet& a, const MySet& b);
std::ostream& operator<<(std::ostream& os, const MySet& set);

#endif // MYSET_H

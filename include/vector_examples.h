#ifndef VECTOR_EXAMPLES_H
#define VECTOR_EXAMPLES_H

#include <vector>
#include <string>

// Класс Date для задания 5
class Date {
private:
    int day;
    int month;
    int year;

public:
    Date();
    Date(int d, int m, int y);
    void print() const;

    // Операторы сравнения
    bool operator<(const Date& other) const;
    bool operator==(const Date& other) const;

    // Геттер для получения года (для проверки будущих дат)
    int getYear() const;
};

void runVectorExamples();
void stringVectorExample();
void dateVectorExample();

// Функция для вывода вектора строк
void printStringVector(const std::vector<std::string>& vec);

// Функция для вывода вектора дат
void printDateVector(const std::vector<Date>& vec);

#endif // VECTOR_EXAMPLES_H

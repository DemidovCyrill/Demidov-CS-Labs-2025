#ifndef LIST_EXAMPLES_H
#define LIST_EXAMPLES_H

#include <list>
#include <string>

// Класс Time для задания 7
class Time {
private:
    int hours;
    int minutes;
    int seconds;

public:
    Time();
    Time(int h, int m, int s);
    void print() const;

    // Операторы сравнения
    bool operator<(const Time& other) const;
    bool operator==(const Time& other) const;

    // Геттер для получения часов (для проверки ночного времени)
    int getHours() const;
};

void runListExamples();
void stringListExample();
void timeListExample();

// Функция для вывода списка строк
void printStringList(const std::list<std::string>& lst);

// Функция для вывода списка времён
void printTimeList(const std::list<Time>& lst);

#endif // LIST_EXAMPLES_H

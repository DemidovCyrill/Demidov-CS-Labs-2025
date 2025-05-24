#ifndef LIST_EXAMPLES_H
#define LIST_EXAMPLES_H

#include <list>
#include <string>

class Time {
private:
    int hours;
    int minutes;
    int seconds;

public:
    Time();
    Time(int h, int m, int s);
    void print() const;

    bool operator<(const Time& other) const;
    bool operator==(const Time& other) const;

    int getHours() const;
};

void runListExamples();
void stringListExample();
void timeListExample();

void printStringList(const std::list<std::string>& lst);

void printTimeList(const std::list<Time>& lst);

#endif // LIST_EXAMPLES_H

#ifndef VECTOR_EXAMPLES_H
#define VECTOR_EXAMPLES_H

#include <vector>
#include <string>

class Date {
private:
    int day;
    int month;
    int year;

public:
    Date();
    Date(int d, int m, int y);
    void print() const;

    bool operator<(const Date& other) const;
    bool operator==(const Date& other) const;

    int getYear() const;
};

void runVectorExamples();
void stringVectorExample();
void dateVectorExample();

void printStringVector(const std::vector<std::string>& vec);

void printDateVector(const std::vector<Date>& vec);

#endif // VECTOR_EXAMPLES_H

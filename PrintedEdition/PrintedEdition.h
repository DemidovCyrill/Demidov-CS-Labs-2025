#ifndef PRINTED_EDITION_H
#define PRINTED_EDITION_H

#include <string>
#include <iostream>

class PrintedEdition {
protected:
    std::string title;
    int pages;
    std::string publisher;
    int year;

public:
    PrintedEdition(const std::string& title, int pages, const std::string& publisher, int year);
    virtual ~PrintedEdition(); // Виртуальный деструктор для абстрактного класса

    // Абстрактный метод для отображения данных
    virtual void show() const = 0;
};

#endif // PRINTED_EDITION_H

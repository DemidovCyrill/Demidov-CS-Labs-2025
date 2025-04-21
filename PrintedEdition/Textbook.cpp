#include "Textbook.h"

Textbook::Textbook(const std::string& title, int pages, const std::string& publisher, int year,
                 const std::string& author, const std::string& genre,
                 const std::string& subject, const std::string& gradeLevel)
    : Book(title, pages, publisher, year, author, genre), subject(subject), gradeLevel(gradeLevel) {
    std::cout << "Textbook()" << std::endl;
}

Textbook::~Textbook() {
    std::cout << "~Textbook()" << std::endl;
}

void Textbook::show() const {
    std::cout << "=== Учебник ===" << std::endl;
    std::cout << "Название: " << title << std::endl;
    std::cout << "Страниц: " << pages << std::endl;
    std::cout << "Издатель: " << publisher << std::endl;
    std::cout << "Год: " << year << std::endl;
    std::cout << "Автор: " << author << std::endl;
    std::cout << "Жанр: " << genre << std::endl;
    std::cout << "Предмет: " << subject << std::endl;
    std::cout << "Уровень обучения: " << gradeLevel << std::endl;
}

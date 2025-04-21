#include "Magazine.h"

Magazine::Magazine(const std::string& title, int pages, const std::string& publisher, int year,
                  int issueNumber, const std::string& issueDate)
    : PrintedEdition(title, pages, publisher, year), issueNumber(issueNumber), issueDate(issueDate) {
    std::cout << "Magazine()" << std::endl;
}

Magazine::~Magazine() {
    std::cout << "~Magazine()" << std::endl;
}

void Magazine::show() const {
    std::cout << "=== Журнал ===" << std::endl;
    std::cout << "Название: " << title << std::endl;
    std::cout << "Страниц: " << pages << std::endl;
    std::cout << "Издатель: " << publisher << std::endl;
    std::cout << "Год: " << year << std::endl;
    std::cout << "Номер выпуска: " << issueNumber << std::endl;
    std::cout << "Дата выпуска: " << issueDate << std::endl;
}

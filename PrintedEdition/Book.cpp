#include "Book.h"

Book::Book(const std::string& title, int pages, const std::string& publisher, int year,
          const std::string& author, const std::string& genre)
    : PrintedEdition(title, pages, publisher, year), author(author), genre(genre) {
    std::cout << "Book()" << std::endl;
}

Book::~Book() {
    std::cout << "~Book()" << std::endl;
}

void Book::show() const {
    std::cout << "=== Книга ===" << std::endl;
    std::cout << "Название: " << title << std::endl;
    std::cout << "Страниц: " << pages << std::endl;
    std::cout << "Издатель: " << publisher << std::endl;
    std::cout << "Год: " << year << std::endl;
    std::cout << "Автор: " << author << std::endl;
    std::cout << "Жанр: " << genre << std::endl;
}

#include <iostream>
#include <cstdlib>
#include "MyVector/MyVector.h"
#include "PrintedEdition/PrintedEdition.h"
#include "PrintedEdition/Magazine.h"
#include "PrintedEdition/Book.h"
#include "PrintedEdition/Textbook.h"

void print(const MyVector<PrintedEdition*>& container) {
    std::cout << "\n===== Содержимое контейнера =====\n";
    if (container.get_size() == 0) {
        std::cout << "Контейнер пуст" << std::endl;
        return;
    }

    for (size_t i = 0; i < container.get_size(); ++i) {
        std::cout << "\nЭлемент [" << i << "]: " << std::endl;
        container[i]->show();
    }
}

void remove(MyVector<PrintedEdition*>& container, size_t index) {
    if (index >= container.get_size()) {
        std::cout << "Ошибка: индекс выходит за пределы контейнера" << std::endl;
        return;
    }

    delete container[index];
    container.delete_element(index);
    std::cout << "Элемент по индексу " << index << " удален" << std::endl;
}

void clear(MyVector<PrintedEdition*>& container) {
    for (size_t i = 0; i < container.get_size(); ++i) {
        delete container[i];
    }

    container = MyVector<PrintedEdition*>();
    std::cout << "Контейнер очищен" << std::endl;
}

void demonstrationMode() {
    std::cout << "===== Демонстрационный режим =====\n";

    MyVector<PrintedEdition*> container;

    std::cout << "\nДобавление объектов в контейнер:" << std::endl;

    container.add_element(new Magazine("National Geographic", 120, "National Geographic Society", 2023, 5, "Май 2023"));
    container.add_element(new Book("1984", 328, "Penguin Books", 1949, "Джордж Оруэлл", "Антиутопия"));
    container.add_element(new Textbook("Высшая математика", 800, "Высшая школа", 2022, "Иванов И.И.", "Учебная литература", "Математика", "Университет"));

    print(container);

    std::cout << "\nУдаление объекта по индексу 1:" << std::endl;
    remove(container, 1);

    print(container);

    std::cout << "\nОчистка контейнера:" << std::endl;
    clear(container);

    print(container);
}

PrintedEdition* createNewObject() {
    char choice;
    std::string title, publisher, author, genre, subject, gradeLevel, issueDate;
    int pages, year, issueNumber;

    std::cout << "\nВыберите тип издания:\n";
    std::cout << "1. Журнал\n";
    std::cout << "2. Книга\n";
    std::cout << "3. Учебник\n";
    std::cout << "Ваш выбор: ";
    std::cin >> choice;
    std::cin.ignore();

    std::cout << "Введите название: ";
    std::getline(std::cin, title);
    std::cout << "Введите количество страниц: ";
    std::cin >> pages;
    std::cin.ignore();
    std::cout << "Введите издателя: ";
    std::getline(std::cin, publisher);
    std::cout << "Введите год издания: ";
    std::cin >> year;
    std::cin.ignore();

    switch (choice) {
        case '1':
            std::cout << "Введите номер выпуска: ";
            std::cin >> issueNumber;
            std::cin.ignore();
            std::cout << "Введите дату выпуска: ";
            std::getline(std::cin, issueDate);
            return new Magazine(title, pages, publisher, year, issueNumber, issueDate);

        case '2':
            std::cout << "Введите автора: ";
            std::getline(std::cin, author);
            std::cout << "Введите жанр: ";
            std::getline(std::cin, genre);
            return new Book(title, pages, publisher, year, author, genre);

        case '3':
            std::cout << "Введите автора: ";
            std::getline(std::cin, author);
            std::cout << "Введите жанр: ";
            std::getline(std::cin, genre);
            std::cout << "Введите предмет: ";
            std::getline(std::cin, subject);
            std::cout << "Введите уровень обучения: ";
            std::getline(std::cin, gradeLevel);
            return new Textbook(title, pages, publisher, year, author, genre, subject, gradeLevel);

        default:
            std::cout << "Неверный выбор. Создаем книгу по умолчанию.\n";
            return new Book("Безымянная книга", 100, "Неизвестное издательство", 2023, "Неизвестный автор", "Неизвестный жанр");
    }
}

void interactiveMode() {
    std::cout << "===== Интерактивный режим =====\n";

    MyVector<PrintedEdition*> container;
    char choice;
    size_t index;

    do {
        std::cout << "\nМеню:\n";
        std::cout << "1. Добавить издание\n";
        std::cout << "2. Показать все издания\n";
        std::cout << "3. Удалить издание по индексу\n";
        std::cout << "4. Очистить контейнер\n";
        std::cout << "Выход - Любая кнпка\n";
        std::cout << "Ваш выбор: ";
        std::cin >> choice;

        switch (choice) {
            case '1':
                container.add_element(createNewObject());
                break;

            case '2':
                print(container);
                break;

            case '3':
                std::cout << "Введите индекс для удаления: ";
                std::cin >> index;
                remove(container, index);
                break;

            case '4':
                clear(container);
                break;
            default:
                clear(container);
                std::cout << "Выход из программы\n";
                break;
        }
    } while (choice != '0');
}

int main() {
    char mode;

    std::cout << "Выберите режим работы:\n";
    std::cout << "1. Демонстрационный режим\n";
    std::cout << "2. Интерактивный режим\n";
    std::cout << "Ваш выбор: ";
    std::cin >> mode;

    if (mode == '1') {
        demonstrationMode();
    } else if (mode == '2') {
        interactiveMode();
    } else {
        std::cout << "Неверный выбор. Попробуйте ещё раз.\n";
        return main();
    }
    std::cout << "\n\nХотите продолжить?\n";
    std::cout << "1 - Продолжить\n";
    std::cout << "Любая кнопка - выйти\n";
    std::cout << "Ваш выбор: ";
    std::cin >> mode;
    if (mode == '1') {
        return main();
    } else {
        std::cout << "Спасибо за работу! Программа завершена.\n";
        return 0;
    }
}

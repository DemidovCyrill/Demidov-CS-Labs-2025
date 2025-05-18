#include "vector_examples.h"
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <ctime>

// Конструкторы для класса Date
Date::Date() : day(1), month(1), year(1970) {}

Date::Date(int d, int m, int y) : day(d), month(m), year(y) {}

// Метод вывода даты
void Date::print() const {
    std::cout << std::setfill('0') << std::setw(2) << day << "."
              << std::setfill('0') << std::setw(2) << month << "."
              << year;
}

// Оператор сравнения <
bool Date::operator<(const Date& other) const {
    if (year != other.year) return year < other.year;
    if (month != other.month) return month < other.month;
    return day < other.day;
}

// Оператор сравнения ==
bool Date::operator==(const Date& other) const {
    return (day == other.day && month == other.month && year == other.year);
}

// Геттер для года
int Date::getYear() const {
    return year;
}

void runVectorExamples() {
    // Запускаем примеры работы с векторами
    stringVectorExample();
    dateVectorExample();
}

// Задание 4: Работа с вектором строк
void stringVectorExample() {
    std::cout << "\nЗадание 4: Работа с вектором строк\n";

    std::vector<std::string> strings;
    std::string input;

    std::cout << "Введите строки (для завершения ввода оставьте строку пустой):\n";

    while (true) {
        std::getline(std::cin, input);
        if (input.empty()) {
            break;
        }
        strings.push_back(input);
    }

    // Печать вектора с номерами строк
    std::cout << "\nВведенный массив строк:\n";
    for (size_t i = 0; i < strings.size(); i++) {
        std::cout << i + 1 << ". " << strings[i] << std::endl;
    }

    // Удаление элемента с индексом 3 (если он существует)
    if (strings.size() > 3) {
        strings.erase(strings.begin() + 3);

        // Печать вектора после удаления элемента
        std::cout << "\nМассив строк после удаления элемента с индексом 3:\n";
        for (size_t i = 0; i < strings.size(); i++) {
            std::cout << i + 1 << ". " << strings[i] << std::endl;
        }
    } else {
        std::cout << "\nВ векторе нет элемента с индексом 3." << std::endl;
    }

    // Печать вектора с помощью функции
    std::cout << "\nПечать вектора с помощью функции:\n";
    printStringVector(strings);
}

// Функция для вывода вектора строк
void printStringVector(const std::vector<std::string>& vec) {
    for (size_t i = 0; i < vec.size(); i++) {
        std::cout << i + 1 << ". " << vec[i] << std::endl;
    }
}

// Задание 5: Работа с вектором дат
void dateVectorExample() {
    std::cout << "\nЗадание 5: Работа с вектором дат\n";

    // Создаем вектор дат и инициализируем его
    std::vector<Date> dates = {
        Date(1, 2, 1963),
        Date(14, 7, 1995),
        Date(7, 12, 2088),
        Date(5, 3, 2030),
        Date(24, 9, 2013),
        Date(19, 9, 2020)
    };

    // Выводим все даты на экран
    std::cout << "Все даты:\n";
    printDateVector(dates);

    // Получаем текущий год
    time_t t = time(nullptr);
    tm* now = localtime(&t);
    int currentYear = now->tm_year + 1900;

    // Создаем новый вектор для дат из будущего
    std::vector<Date> futureDates;
    for (const auto& date : dates) {
        if (date.getYear() > currentYear) {
            futureDates.push_back(date);
        }
    }

    // Выводим даты из будущего
    std::cout << "\nДаты из будущего (после " << currentYear << " года):\n";
    if (futureDates.empty()) {
        std::cout << "Нет дат из будущего." << std::endl;
    } else {
        printDateVector(futureDates);
    }
}

// Функция для вывода вектора дат
void printDateVector(const std::vector<Date>& vec) {
    for (size_t i = 0; i < vec.size(); i++) {
        std::cout << i + 1 << ". ";
        vec[i].print();
        std::cout << std::endl;
    }
}

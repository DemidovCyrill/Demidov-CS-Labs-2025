#include "list_examples.h"
#include <iostream>
#include <list>
#include <string>
#include <iomanip>

// Конструкторы для класса Time
Time::Time() : hours(0), minutes(0), seconds(0) {}

Time::Time(int h, int m, int s) : hours(h), minutes(m), seconds(s) {}

// Метод вывода времени
void Time::print() const {
    std::cout << std::setfill('0') << std::setw(2) << hours << ":"
              << std::setfill('0') << std::setw(2) << minutes << ":"
              << std::setfill('0') << std::setw(2) << seconds;
}

// Оператор сравнения <
bool Time::operator<(const Time& other) const {
    if (hours != other.hours) return hours < other.hours;
    if (minutes != other.minutes) return minutes < other.minutes;
    return seconds < other.seconds;
}

// Оператор сравнения ==
bool Time::operator==(const Time& other) const {
    return (hours == other.hours && minutes == other.minutes && seconds == other.seconds);
}

// Геттер для часов
int Time::getHours() const {
    return hours;
}

void runListExamples() {
    // Запускаем примеры работы со списками
    stringListExample();
    timeListExample();
}

// Задание 6: Работа со списком строк
void stringListExample() {
    std::cout << "\nЗадание 6: Работа со списком строк\n";

    std::list<std::string> strings;
    std::string input;

    std::cout << "Введите строки (для завершения ввода оставьте строку пустой):\n";

    while (true) {
        std::getline(std::cin, input);
        if (input.empty()) {
            break;
        }
        strings.push_back(input);
    }

    // Печать списка с номерами строк
    std::cout << "\nВведенный массив строк:\n";
    int index = 1;
    for (const auto& str : strings) {
        std::cout << index++ << ". " << str << std::endl;
    }

    // Удаление элемента с индексом 3 (если он существует)
    if (strings.size() > 3) {
        auto it = strings.begin();
        std::advance(it, 3);
        strings.erase(it);

        // Печать списка после удаления элемента
        std::cout << "\nМассив строк после удаления элемента с индексом 3:\n";
        index = 1;
        for (const auto& str : strings) {
            std::cout << index++ << ". " << str << std::endl;
        }
    } else {
        std::cout << "\nВ списке нет элемента с индексом 3." << std::endl;
    }

    // Печать списка с помощью функции
    std::cout << "\nПечать списка с помощью функции:\n";
    printStringList(strings);
}

// Функция для вывода списка строк
void printStringList(const std::list<std::string>& lst) {
    int index = 1;
    for (const auto& str : lst) {
        std::cout << index++ << ". " << str << std::endl;
    }
}

// Задание 7: Работа со списком времён
void timeListExample() {
    std::cout << "\nЗадание 7: Работа со списком времён\n";

    // Создаем список времён и инициализируем его
    std::list<Time> times = {
        Time(1, 2, 63),
        Time(14, 57, 19),
        Time(7, 32, 20),
        Time(5, 13, 23),
        Time(10, 19, 45),
        Time(19, 9, 59)
    };

    // Выводим все времена на экран
    std::cout << "Все времена:\n";
    printTimeList(times);

    // Создаем новый список для ночных времен (с 0 до 5 часов)
    std::list<Time> nightTimes;
    for (const auto& time : times) {
        if (time.getHours() >= 0 && time.getHours() < 5) {
            nightTimes.push_back(time);
        }
    }

    // Выводим ночные времена
    std::cout << "\nНочные времена (с 0 до 5 часов):\n";
    if (nightTimes.empty()) {
        std::cout << "Нет ночных времен." << std::endl;
    } else {
        printTimeList(nightTimes);
    }
}

// Функция для вывода списка времён
void printTimeList(const std::list<Time>& lst) {
    int index = 1;
    for (const auto& time : lst) {
        std::cout << index++ << ". ";
        time.print();
        std::cout << std::endl;
    }
}

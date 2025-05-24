#include "map_examples.h"
#include <iostream>
#include <map>
#include <string>

void runMapExamples() {
    inventoryMapExample();
    schoolClassesMapExample();
}

template<typename K, typename V>
void printMap(const std::map<K, V>& m) {
    for (const auto& [key, value] : m) {
        std::cout << key << " - " << value << std::endl;
    }
}

void inventoryMapExample() {
    std::cout << "\nЗадание 8: Работа с отображением товаров\n";

    std::map<std::string, int> inventory = {
        {"Отверка", 0},
        {"Молоток", 10},
        {"Гайки", 100},
        {"Профиль", 0},
        {"Уголок", 9},
        {"Доска", 17}
    };

    std::cout << "Товары с ненулевым количеством:\n";
    for (const auto& [product, quantity] : inventory) {
        if (quantity > 0) {
            std::cout << product << " - " << quantity << std::endl;
        }
    }
}

void schoolClassesMapExample() {
    std::cout << "\nЗадание 9: Работа с отображением классов школы\n";

    std::map<std::string, int> schoolClasses = {
        {"1а", 21},
        {"1б", 20},
        {"2", 25},
        {"3а", 20},
        {"3б", 23},
        {"4а", 25},
        {"4б", 25},
        {"5а", 26},
        {"5б", 25},
        {"6a", 19},
        {"6б", 18},
        {"7а", 26},
        {"7б", 25},
        {"8", 25},
        {"9", 17},
        {"10", 15},
        {"11", 14}
    };

    int totalStudents = 0;
    for (const auto& [className, students] : schoolClasses) {
        totalStudents += students;
    }

    std::cout << "Общее количество учащихся в школе: " << totalStudents << std::endl;

    std::cout << "\nСписок классов и количество учащихся:\n";
    printMap(schoolClasses);
}

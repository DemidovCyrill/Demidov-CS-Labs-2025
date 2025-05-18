#include <iostream>
#include "string_examples.h"
#include "vector_examples.h"
#include "list_examples.h"
#include "map_examples.h"

int main() {
    std::cout << "=== Демонстрация возможностей STL ===" << std::endl;

    // Задание 1-3: Примеры работы со строками
    std::cout << "\n=== Примеры работы со строками ===\n";
    runStringExamples();

    // Задание 4-5: Примеры работы с векторами
    std::cout << "\n=== Примеры работы с векторами ===\n";
    runVectorExamples();

    // Задание 6-7: Примеры работы со списками
    std::cout << "\n=== Примеры работы со списками ===\n";
    runListExamples();

    // Задание 8-9: Примеры работы с отображениями
    std::cout << "\n=== Примеры работы с отображениями ===\n";
    runMapExamples();

    return 0;
}

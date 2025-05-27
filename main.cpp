#include <iostream>
#include "string_examples.h"
#include "vector_examples.h"
#include "list_examples.h"
#include "map_examples.h"

int main() {
    std::cout << "=== Демонстрация возможностей STL ===" << std::endl;

    std::cout << "\n=== Примеры работы со строками ===\n";
    runStringExamples();

    std::cout << "\n=== Примеры работы с векторами ===\n";
    runVectorExamples();

    std::cout << "\n=== Примеры работы со списками ===\n";
    runListExamples();

    std::cout << "\n=== Примеры работы с отображениями ===\n";
    runMapExamples();

    return 0;
}

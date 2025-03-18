#include <iostream>
#include "MySet/MySet.h"
#include "MyVector/MyVector.h"

int main() {
    MySet<int> set1;
    set1.add_element(1);
    set1.add_element(4);
    set1.add_element(5);
    set1.add_element(6);

    MySet<int> set2;
    set2.add_element(1);
    set2.add_element(2);
    set2.add_element(3);
    set2.add_element(4);

    std::cout << "Элементы множества 1: " << set1;
    std::cout << "Элементы множества 2: " << set2;

    MySet<int> union_set = set1 + set2;
    MySet<int> intersection_set = set1 * set2;
    MySet<int> difference_set = set1 - set2;

    std::cout << "Сумма множеств: " << union_set;

    std::cout << "Пересечение множеств: " << intersection_set;

    std::cout << "Разность множеств: " << difference_set;

    return 0;
}

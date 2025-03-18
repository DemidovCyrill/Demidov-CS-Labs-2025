#include <iostream>
#include "MySet/MySet.h"
#include "MyVector/MyVector.h"

int main() {
    MySet<int> set1;
    set1.add_element(1);
    set1.add_element(4);
    set1.add_element(5);
    set1.add_element(6);

    // MySet<int> set2;
    // set2.add_element(1);
    // set2.add_element(2);
    // set2.add_element(3);
    // set2.add_element(4);

    // MySet<int> union_set = set1 + set2;
    // MySet<int> intersection_set = set1 * set2;
    // MySet<int> difference_set = set1 - set2;

    // std::cout << "Union: ";
    // for (size_t i = 0; i < union_set.get_size(); ++i)
    //     std::cout << union_set[i] << " ";
    // std::cout << std::endl;
    // std::cout << "Intersection: ";
    // for (size_t i = 0; i < intersection_set.get_size(); ++i)
    //     std::cout << intersection_set[i] << " ";
    // std::cout << std::endl;

    // std::cout << "Difference: ";
    // for (size_t i = 0; i < difference_set.get_size(); ++i)
    //     std::cout << difference_set[i] << " ";
    // std::cout << std::endl;

    return 0;
}

#include <iostream>
#include "mymath/mymath.h"
#include "mymath_2/mymath_2.h"

int main() {
    setlocale(LC_ALL, "Russian");
    std::cout << "Я умею суммировать! Зацени 10+32=";
    std::cout << mymath::sum(10, 32) << std::endl;
    std::cout << "Я умею умножать! Зацени 10*32=";
    std::cout << mymath_2::multiplication(10, 32) << std::endl;

    return 0;
}

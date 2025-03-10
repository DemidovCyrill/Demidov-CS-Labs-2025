#include <iostream>
#include "MyStack/MyStack.h"

void Multipliers(int n, MyStack<int> &stack) {
    if (n <= 1) {
        return;
    }
    int divisor = 2;
    while (n > 1) {
        if (n % divisor == 0) {
            stack.append(divisor);
            n /= divisor;
        } else {
            divisor++;
        }
    }
}

int main() {

    std::cout << "Программа лабораторной работы №4 создаёт стек из простых множетелей числа и выводит его по возрастанию и убыванию" << std::endl;
    std::cout << "Введите ваше число: ";
    int number;
    std::cin >> number;
    std::cout << std::endl;
    MyStack<int> stack;
    Multipliers(number, stack);

    MyStack<int> stackCopy = stack;
    std::cout << number << " = ";
    bool first = false;
    while (!stack.any()) {
        if (first) {
            std::cout << " * ";
        }
        std::cout << stack.get();
        stack.pop();
        first = true;
    }
    std::cout << std::endl << std::endl;

    MyStack<int> tempStack;
    while (!stackCopy.any()) {
        tempStack.append(stackCopy.get());
        stackCopy.pop();
    }

    std::cout << number << " = ";
    first = true;
    while (!tempStack.any()) {
        if (!first) {
            std::cout << " * ";
        }
        std::cout << tempStack.get();
        tempStack.pop();
        first = false;
    }
    std::cout << std::endl;

    return 0;
}

#include <iostream>
#include <fstream>
#include "MyStack/MyStack.h"

void Multipliers(int n, MyStack<int> &stack) {
    if (n < 0) {
        throw std::invalid_argument("Ввод отрицательных чисел некорректен!!!");
    }
    if (n == 0) {
        throw std::invalid_argument("Ввод нуля некорректен!!!");
    }
    if (n == 1) {
        stack.append(1);
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


void ExtraTask() {
    std::cout << "\nДемонстрация работы со стеками символов:\n";

    std::cout << "\n1. Простой стек: ";
    MyStack<char> stackABC;
    stackABC.append('A');
    stackABC.append('B');
    stackABC.append('C');
    std::cout << stackABC;

    std::cout << "\n2. Стек с использованием конструктора копирования: ";
    MyStack<char> stack2;
    stack2.append('A');
    stack2.append('B');
    stack2.append('C');
    std::cout << stack2;

    std::cout << "\n3. Стек с использованием оператора присваивания: ";
    MyStack<char> stack3;
    stack3.append('A');
    stack3.append('B');
    stack3.append('C');
    std::cout << stack3;

    MyStack<char> stack3Assigned;
    stack3Assigned = stack3;
    // std::cout << stack3Assigned;
}



int main() {
    try {
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
        std::cout << tempStack;


        ExtraTask();

        return 0;
    }
    catch (std::invalid_argument& e){
        std::cout << e.what() << std::endl;
    }
}

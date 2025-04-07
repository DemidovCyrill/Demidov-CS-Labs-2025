#include <iostream>
#include <string>
#include "term/term.h"
#include "term/polynomial.h"

void demoTerm() {
    std::cout << "=== Демонстрация класса Term ===" << std::endl;

    // Создаем термы
    Term t1(3, 2);  // 3x^2
    Term t2(-1, 2);  // -x^2
    Term t3(5, 5);  // 5x^5
    Term t4(1, 1);  // x
    Term t5(7, 0);  // 7

    // Выводим термы
    std::cout << "t1: " << t1 << std::endl;
    std::cout << "t2: " << t2 << std::endl;
    std::cout << "t3: " << t3 << std::endl;
    std::cout << "t4: " << t4 << std::endl;
    std::cout << "t5: " << t5 << std::endl;

    // Складываем термы
    Term t6 = t1 + t2;  // 3x^2 + (-x^2) = 2x^2
    std::cout << "t1 + t2: " << t6 << std::endl;

    // Парсим термы с клавиатуры
    std::cout << "Введите терм: ";
    Term t7;
    std::cin >> t7;
    std::cout << "Распознанный терм: " << t7 << std::endl;
}

void demoPolynomial() {
    std::cout << "=== Демонстрация класса Polynomial ===" << std::endl;

    // Создаем полиномы
    Polynomial p1;  // 0
    Polynomial p2(5);  // 5
    Polynomial p3(Term(3, 2));  // 3x^2

    // Выводим полиномы
    std::cout << "p1: " << p1 << std::endl;
    std::cout << "p2: " << p2 << std::endl;
    std::cout << "p3: " << p3 << std::endl;

    // Складываем полиномы
    Polynomial p4 = p2 + p3;  // 5 + 3x^2
    std::cout << "p2 + p3: " << p4 << std::endl;

    // Умножаем полиномы
    Polynomial p5 = p2 * p3;  // 5 * 3x^2 = 15x^2
    std::cout << "p2 * p3: " << p5 << std::endl;

    // Парсим полином
    std::cout << "Введите полином: ";
    std::cin.ignore();  // Игнорируем остаток строки
    Polynomial p6;
    std::cin >> p6;
    std::cout << "Распознанный полином: " << p6 << std::endl;

    // Присваиваем полином
    p1 = p6;
    std::cout << "p1 = p6: " << p1 << std::endl;

    // Сложение с присваиванием
    p1 += p2;
    std::cout << "p1 += p2: " << p1 << std::endl;

    // Умножение с присваиванием
    p1 *= p3;
    std::cout << "p1 *= p3: " << p1 << std::endl;
}

int main() {
    int choice;
    std::cout << "Выберите режим:" << std::endl;
    std::cout << "1. Демонстрационный режим" << std::endl;
    std::cout << "2. Интерактивный режим" << std::endl;
    std::cout << "Выбор: ";
    std::cin >> choice;

    if (choice == 1) {
        // Демо-режим
        demoTerm();
        demoPolynomial();
    } else if (choice == 2) {
        // Интерактивный режим
        std::cout << "=== Операции с термами ===" << std::endl;
        std::cout << "Введите первый терм: ";
        Term t1;
        std::cin >> t1;
        std::cout << "Распознанный терм: " << t1 << std::endl;

        std::cout << "Введите второй терм (с той же степенью): ";
        Term t2;
        std::cin >> t2;
        std::cout << "Распознанный терм: " << t2 << std::endl;

        try {
            Term t3 = t1 + t2;
            std::cout << "t1 + t2: " << t3 << std::endl;
        } catch (const std::invalid_argument& e) {
            std::cout << "Ошибка: " << e.what() << std::endl;
        }

        std::cout << "=== Операции с полиномами ===" << std::endl;
        std::cout << "Введите первый полином: ";
        std::cin.ignore();  // Игнорируем остаток строки
        Polynomial p1;
        std::cin >> p1;
        std::cout << "Распознанный полином: " << p1 << std::endl;

        std::cout << "Введите второй полином: ";
        Polynomial p2;
        std::cin.ignore();  // Игнорируем остаток строки
        std::cin >> p2;
        std::cout << "Распознанный полином: " << p2 << std::endl;

        Polynomial p3 = p1 + p2;
        std::cout << "p1 + p2: " << p3 << std::endl;

        Polynomial p4 = p1 * p2;
        std::cout << "p1 * p2: " << p4 << std::endl;
    } else {
        std::cout << "Неверный выбор!" << std::endl;
    }

    return 0;
}

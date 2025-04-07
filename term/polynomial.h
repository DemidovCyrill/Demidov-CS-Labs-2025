// polynomial.h
#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include "term.h"
#include <iostream>

class Polynomial {
private:
    Term* poly;
    int size;      // Текущее количество термов
    int capacity;  // Текущая емкость массива poly
    int degree;    // Наивысшая степень полинома

    enum Order {
        ASCENDING,
        DESCENDING
    };
    Order order_;  // Порядок хранения термов

    // Вспомогательные методы
    void resize(int newCapacity);
    void addTerm(const Term& term);
    void updateDegree();
    void sortTerms();

public:
    // Конструкторы
    Polynomial();                    // Представляет 0
    Polynomial(int constant);        // Представляет константный полином
    Polynomial(const Term& term);    // Представляет полином с одним термом
    Polynomial(const Polynomial& other); // Конструктор копирования
    ~Polynomial();                   // Деструктор

    // Операторы присваивания
    Polynomial& operator=(const Polynomial& other);
    Polynomial& operator+=(const Polynomial& other);
    Polynomial& operator*=(const Polynomial& other);

    // Дружественные операторы
    friend Polynomial operator+(const Polynomial& p1, const Polynomial& p2);
    friend Polynomial operator*(const Polynomial& p1, const Polynomial& p2);

    // Операторы потоков
    friend std::istream& operator>>(std::istream& is, Polynomial& poly);
    friend std::ostream& operator<<(std::ostream& os, const Polynomial& poly);
};

#endif // POLYNOMIAL_H

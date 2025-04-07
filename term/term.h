// term.h
#ifndef TERM_H
#define TERM_H

#include <iostream>

class Polynomial; // Предварительное объявление

class Term {
private:
    int coefficient;
    int exponent;

public:
    // Конструкторы
    Term();                    // Для представления 0x^0
    Term(int coef);            // Для представления coef*x^0
    Term(int coef, int exp);   // Для представления coef*x^exp

    // Геттеры
    int getCoefficient() const;
    int getExponent() const;

    void setCoefficient(int c);
    void setExponent(int c);

    // Операторы
    friend Term operator+(const Term& t1, const Term& t2);
    friend std::istream& operator>>(std::istream& is, Term& term);
    friend std::ostream& operator<<(std::ostream& os, const Term& term);

    // Дружественный класс
    friend class Polynomial;
};

#endif // TERM_H

// term.cpp
#include "term.h"

// Конструкторы
Term::Term() : coefficient(0), exponent(0) {}
Term::Term(int coef) : coefficient(coef), exponent(0) {}
Term::Term(int coef, int exp) : coefficient(coef), exponent(exp) {}

// Геттеры
int Term::getCoefficient() const { return coefficient; }
int Term::getExponent() const { return exponent; }

void Term::setCoefficient(int c) {coefficient = c;}
void Term::setExponent(int c) {exponent = c;}

// Оператор сложения
Term operator+(const Term& t1, const Term& t2) {
    if (t1.exponent != t2.exponent) {
        throw std::invalid_argument("Нельзя складывать термы с разными степенями");
    }
    return Term(t1.coefficient + t2.coefficient, t1.exponent);
}

// Оператор ввода
std::istream& operator>>(std::istream& is, Term& term) {
    // Пропускаем пробелы
    is >> std::ws;

    // Читаем коэффициент (если есть)
    int coef = 1;  // По умолчанию 1 (например, "x^2")
    int exp = 0;   // По умолчанию 0 (для константы)

    if (isdigit(is.peek())) {
        is >> coef;
    }

    // Проверяем наличие переменной 'x'
    is >> std::ws;
    if (is.peek() == 'x') {
        is.get();  // Пропускаем 'x'
        exp = 1;   // По умолчанию 1 (например, "3x")

        // Проверяем наличие степени
        is >> std::ws;
        if (is.peek() == '^') {
            is.get();  // Пропускаем '^'
            is >> std::ws;
            is >> exp;
        }
    }

    term.coefficient = coef;
    term.exponent = exp;

    return is;
}

// Оператор вывода
std::ostream& operator<<(std::ostream& os, const Term& term) {
    if (term.coefficient == 0) {
        return os;  // Не выводим нулевые термы
    }

    if (term.exponent == 0) {
        // Выводим только коэффициент для констант
        os << term.coefficient;
    } else if (term.exponent == 1) {
        // Для линейных членов (x^1)
        if (term.coefficient == 1) {
            os << "x";
        } else if (term.coefficient == -1) {
            os << "-x";
        } else {
            os << term.coefficient << "x";
        }
    } else {
        // Для членов высших степеней
        if (term.coefficient == 1) {
            os << "x^" << term.exponent;
        } else if (term.coefficient == -1) {
            os << "-x^" << term.exponent;
        } else {
            os << term.coefficient << "x^" << term.exponent;
        }
    }

    return os;
}

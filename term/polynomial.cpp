// polynomial.cpp
#include "polynomial.h"
#include <sstream>
#include <string>
#include <cctype>

// Вспомогательные методы
void Polynomial::resize(int newCapacity) {
    Term* newPoly = new Term[newCapacity];
    for (int i = 0; i < size; ++i) {
        newPoly[i] = poly[i];
    }
    delete[] poly;
    poly = newPoly;
    capacity = newCapacity;
}

void Polynomial::addTerm(const Term& term) {
    if (term.coefficient == 0) {
        return;  // Не добавляем нулевые термы
    }

    // Проверяем, существует ли терм с такой же степенью
    for (int i = 0; i < size; ++i) {
        if (poly[i].exponent == term.exponent) {
            // Складываем коэффициенты, если степени совпадают
            poly[i].coefficient += term.coefficient;

            // Если коэффициент становится нулевым, удаляем терм
            if (poly[i].coefficient == 0) {
                for (int j = i; j < size - 1; ++j) {
                    poly[j] = poly[j + 1];
                }
                --size;
            }

            // Обновляем степень, если необходимо
            updateDegree();
            sortTerms();
            return;
        }
    }

    // Если терм с совпадающей степенью не найден

    // Проверяем наличие свободного места
    if (size == capacity) {
        resize(capacity * 2);
    }

    // Добавляем новый терм
    poly[size++] = term;

    // Обновляем степень, если необходимо
    if (term.exponent > degree) {
        degree = term.exponent;
    }

    // Сортируем термы
    sortTerms();
}

void Polynomial::updateDegree() {
    degree = 0;
    for (int i = 0; i < size; ++i) {
        if (poly[i].exponent > degree) {
            degree = poly[i].exponent;
        }
    }
}

void Polynomial::sortTerms() {
    // Простая сортировка пузырьком
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {
            bool shouldSwap;

            if (order_ == ASCENDING) {
                shouldSwap = poly[j].exponent > poly[j + 1].exponent;
            } else {  // DESCENDING
                shouldSwap = poly[j].exponent < poly[j + 1].exponent;
            }

            if (shouldSwap) {
                Term temp = poly[j];
                poly[j] = poly[j + 1];
                poly[j + 1] = temp;
            }
        }
    }
}

// Конструкторы
Polynomial::Polynomial() : poly(new Term[10]), size(0), capacity(10), degree(0), order_(DESCENDING) {}

Polynomial::Polynomial(int constant) : poly(new Term[10]), size(0), capacity(10), degree(0), order_(DESCENDING) {
    if (constant != 0) {
        addTerm(Term(constant, 0));
    }
}

Polynomial::Polynomial(const Term& term) : poly(new Term[10]), size(0), capacity(10), degree(0), order_(DESCENDING) {
    if (term.coefficient != 0) {
        addTerm(term);
    }
}

Polynomial::Polynomial(const Polynomial& other) : poly(new Term[other.capacity]), size(other.size), capacity(other.capacity), degree(other.degree), order_(other.order_) {
    for (int i = 0; i < size; ++i) {
        poly[i] = other.poly[i];
    }
}

Polynomial::~Polynomial() {
    delete[] poly;
}

// Операторы присваивания
Polynomial& Polynomial::operator=(const Polynomial& other) {
    if (this != &other) {
        delete[] poly;
        capacity = other.capacity;
        size = other.size;
        degree = other.degree;
        order_ = other.order_;

        poly = new Term[capacity];
        for (int i = 0; i < size; ++i) {
            poly[i] = other.poly[i];
        }
    }
    return *this;
}

Polynomial& Polynomial::operator+=(const Polynomial& other) {
    for (int i = 0; i < other.size; ++i) {
        addTerm(other.poly[i]);
    }
    return *this;
}

Polynomial& Polynomial::operator*=(const Polynomial& other) {
    Polynomial result;

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < other.size; ++j) {
            int coef = poly[i].coefficient * other.poly[j].coefficient;
            int exp = poly[i].exponent + other.poly[j].exponent;
            result.addTerm(Term(coef, exp));
        }
    }

    *this = result;
    return *this;
}

// Дружественные операторы
Polynomial operator+(const Polynomial& p1, const Polynomial& p2) {
    Polynomial result = p1;
    result += p2;
    return result;
}

Polynomial operator*(const Polynomial& p1, const Polynomial& p2) {
    Polynomial result = p1;
    result *= p2;
    return result;
}

// Операторы потоков
std::istream& operator>>(std::istream& is, Polynomial& poly) {
    // Очищаем существующий полином
    poly = Polynomial();

    std::string input;
    std::getline(is, input);

    // Добавляем '+' в начале, если нет знака
    if (!input.empty() && input[0] != '+' && input[0] != '-') {
        input = "+" + input;
    }

    // Разбираем ввод
    size_t pos = 0;
    while (pos < input.length()) {
        // Пропускаем пробелы
        while (pos < input.length() && std::isspace(input[pos])) {
            pos++;
        }

        if (pos >= input.length()) {
            break;
        }

        // Получаем знак
        bool isNegative = (input[pos] == '-');
        pos++;

        // Пропускаем пробелы после знака
        while (pos < input.length() && std::isspace(input[pos])) {
            pos++;
        }

        // Находим конец терма (следующий + или -)
        size_t termStart = pos;
        size_t termEnd = pos;

        while (termEnd < input.length()) {
            if (input[termEnd] == '+' || input[termEnd] == '-') {
                break;
            }
            termEnd++;
        }

        // Извлекаем строку терма
        std::string termStr = input.substr(termStart, termEnd - termStart);

        // Разбираем терм
        std::istringstream termStream(termStr);
        Term term;
        termStream >> term;

        // Применяем знак
        if (isNegative) {
            term.setCoefficient(-term.getCoefficient());
        }

        // Добавляем терм в полином
        poly.addTerm(term);

        // Переходим к следующему терму
        pos = termEnd;
    }

    return is;
}

std::ostream& operator<<(std::ostream& os, const Polynomial& poly) {
    if (poly.size == 0) {
        return os << "0";
    }

    bool firstTerm = true;

    for (int i = 0; i < poly.size; ++i) {
        const Term& term = poly.poly[i];

        if (term.getCoefficient() == 0) {
            continue;  // Пропускаем нулевые термы
        }

        if (firstTerm) {
            // Первый терм не требует пробела перед ним
            firstTerm = false;

            if (term.getCoefficient() < 0) {
                // Отрицательный первый терм
                if (term.getCoefficient() == -1) {
                    if (term.getExponent() == 0) {
                        os << "-1";
                    } else if (term.getExponent() == 1) {
                        os << "-x";
                    } else {
                        os << "-x^" << term.getExponent();
                    }
                } else {
                    if (term.getExponent() == 0) {
                        os << term.getCoefficient();
                    } else if (term.getExponent() == 1) {
                        os << term.getCoefficient() << "x";
                    } else {
                        os << term.getCoefficient() << "x^" << term.getExponent();
                    }
                }
            } else {
                // Положительный первый терм
                if (term.getCoefficient() == 1) {
                    if (term.getExponent() == 0) {
                        os << "1";
                    } else if (term.getExponent() == 1) {
                        os << "x";
                    } else {
                        os << "x^" << term.getExponent();
                    }
                } else {
                    if (term.getExponent() == 0) {
                        os << term.getCoefficient();
                    } else if (term.getExponent() == 1) {
                        os << term.getCoefficient() << "x";
                    } else {
                        os << term.getCoefficient() << "x^" << term.getExponent();
                    }
                }
            }
        } else {
            // Последующие термы требуют знака и пробела
            if (term.getCoefficient() > 0) {
                os << " + ";

                if (term.getCoefficient() == 1) {
                    if (term.getExponent() == 0) {
                        os << "1";
                    } else if (term.getExponent() == 1) {
                        os << "x";
                    } else {
                        os << "x^" << term.getExponent();
                    }
                } else {
                    if (term.getExponent() == 0) {
                        os << term.getCoefficient();
                    } else if (term.getExponent() == 1) {
                        os << term.getCoefficient() << "x";
                    } else {
                        os << term.getCoefficient() << "x^" << term.getExponent();
                    }
                }
            } else {
                os << " - ";

                if (term.getCoefficient() == -1) {
                    if (term.getExponent() == 0) {
                        os << "1";
                    } else if (term.getExponent() == 1) {
                        os << "x";
                    } else {
                        os << "x^" << term.getExponent();
                    }
                } else {
                    if (term.getExponent() == 0) {
                        os << -term.getCoefficient();
                    } else if (term.getExponent() == 1) {
                        os << -term.getCoefficient() << "x";
                    } else {
                        os << -term.getCoefficient() << "x^" << term.getExponent();
                    }
                }
            }
        }
    }

    return os;
}

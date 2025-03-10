#include <iostream>
#include "MyStack.h"

template<class INF>
MyStack<INF>::MyStack(void) {
    top = nullptr;
}

// Конструктор копирования
template<class INF>
MyStack<INF>::MyStack(const MyStack& other) {
    top = nullptr;
    if (other.top != nullptr) {
        // Создаем временный стек для инвертирования порядка
        MyStack<INF> temp;
        Node* current = other.top;
        // Сначала копируем все элементы в обратном порядке
        while (current != nullptr) {
            temp.append(current->d);
            current = current->next;
        }
        // Затем копируем из временного стека в правильном порядке
        while (!temp.empty()) {
            append(temp.get());
            temp.pop();
        }
    }
}

// Перегрузка оператора =
template<class INF>
MyStack<INF>& MyStack<INF>::operator=(const MyStack& other) {
    if (this != &other) {
        // Очищаем текущий стек
        while (!empty()) {
            pop();
        }

        if (other.top != nullptr) {
            // Создаем временный стек для инвертирования порядка
            MyStack<INF> temp;
            Node* current = other.top;
            // Сначала копируем все элементы в обратном порядке
            while (current != nullptr) {
                temp.append(current->d);
                current = current->next;
            }
            // Затем копируем из временного стека в правильном порядке
            while (!temp.empty()) {
                append(temp.get());
                temp.pop();
            }
        }
    }
    return *this;
}

// Деструктор
template<class INF>
MyStack<INF>::~MyStack(void) {
    while (!empty()) {
        pop();
    }
}

// Проверка на пустоту
template<class INF>
bool MyStack<INF>::empty(void) {
    return top == nullptr;
}

// Добавление элемента в стек
template<class INF>
bool MyStack<INF>::append(INF n) {
    Node* newNode = new Node(n);
    if (newNode == nullptr) {
        return false; // Не удалось выделить память
    }
    newNode->next = top;
    top = newNode;
    return true;
}

// Удаление элемента из стека
template<class INF>
bool MyStack<INF>::pop(void) {
    if (empty()) {
        return false; // Стек пуст
    }
    Node* temp = top;
    top = top->next;
    delete temp;
    return true;
}

// Получение значения верхнего элемента
template<class INF>
INF MyStack<INF>::get(void) {
    if (empty()) {
        return INF(); // Возвращаем значение по умолчанию
    }
    return top->d;
}

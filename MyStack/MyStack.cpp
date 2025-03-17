#ifndef MyStack_cpp
#define MyStack_cpp
#include "MyStack.h"
#include <fstream>
#include <iostream>

template<class INF>
MyStack<INF>::MyStack(void) {
    top = nullptr;
}


template<class INF>
MyStack<INF>::MyStack(const MyStack& other) {
    top = nullptr;

    if (other.top != nullptr) {

        MyStack<INF> temp;
        Node* current = other.top;

        while (current != nullptr) {
            temp.append(current->d);
            current = current -> next;
        }


        while (!temp.any()) {
            append(temp.get());
            temp.pop();
        }
    }
}


template<class INF>
MyStack<INF>& MyStack<INF>::operator=(const MyStack& other) {
    if (this != &other) {

        while (!any()) {
            pop();
        }

        if (other.top != nullptr) {

            MyStack<INF> temp;
            Node* current = other.top;

            while (current != nullptr) {
                temp.append(current->d);
                current = current->next;
            }

            while (!temp.any()) {
                append(temp.get());
                temp.pop();
            }
        }
    }
    return *this;
}


template<class INF>
MyStack<INF>::~MyStack(void) {
    while (!any()) {
        pop();
    }
}


template<class INF>
bool MyStack<INF>::any(void) {
    return top == nullptr;
}


template<class INF>
bool MyStack<INF>::append(INF n) {
    Node* newNode = new Node(n);
    if (newNode == nullptr) {
        return false;
    }
    newNode -> next = top;
    top = newNode;
    return true;
}


template<class INF>
bool MyStack<INF>::pop(void) {
    if (any()) {
        return false;
    }
    Node* temp = top;
    top = top -> next;
    delete temp;
    return true;
}


template<class INF>
INF MyStack<INF>::get(void) {
    if (any()) {
        return INF();
    }
    return top -> d;
}

std::ostream& operator<<(std::ostream& os, const MyStack<int>& stack) {
    MyStack<int> stackCopy = stack;
    bool first = false;
    while (!stackCopy.any()) {
        if (first) {
            os << " * ";
        }
        os << stackCopy.get();
        stackCopy.pop();
        first = true;
    }
    std::cout << std::endl;
    return os;
}

std::ostream& operator<<(std::ostream& os, const MyStack<char>& stack) {
    MyStack<char> stackCopy = stack;
    bool first = false;
    while (!stackCopy.any()) {
        if (first) {
            os << " ";
        }
        os << stackCopy.get();
        stackCopy.pop();
        first = true;
    }
    std::cout << std::endl;
    return os;
}

template<class INF>
std::ostream& operator<<(std::ostream& os, const MyStack<INF>& stack);

#endif

#include "ContainerFunctions.h"

void print(const MyStack<PrintedEdition*>& stack) {
    if (stack.any()) {
        std::cout << "Container is empty" << std::endl;
        return;
    }

    std::cout << "\n--- Container Content ---\n";

    MyStack<PrintedEdition*> tempStack = stack;
    MyStack<PrintedEdition*> reverseStack;

    while (!tempStack.any()) {
        reverseStack.append(tempStack.get());
        tempStack.pop();
    }

    int index = 0;
    while (!reverseStack.any()) {
        PrintedEdition* item = reverseStack.get();
        std::cout << "[" << index << "] ";
        item->show();
        reverseStack.pop();
        index++;
    }

    std::cout << "------------------------\n";
}

void remove(MyStack<PrintedEdition*>& stack, int index) {
    if (stack.any()) {
        std::cout << "Container is empty" << std::endl;
        return;
    }

    MyStack<PrintedEdition*> tempStack;
    MyStack<PrintedEdition*> resultStack;

    while (!stack.any()) {
        tempStack.append(stack.get());
        stack.pop();
    }

    int currentIndex = 0;
    PrintedEdition* itemToRemove = nullptr;

    while (!tempStack.any()) {
        PrintedEdition* current = tempStack.get();
        tempStack.pop();

        if (currentIndex != index) {
            resultStack.append(current);
        } else {
            itemToRemove = current;
        }
        currentIndex++;
    }

    while (!resultStack.any()) {
        stack.append(resultStack.get());
        resultStack.pop();
    }

    if (itemToRemove) {
        delete itemToRemove;
        std::cout << "Элемент по индексу " << index << " успешно удален" << std::endl;
    } else {
        std::cout << "Индекс " << index << " находится за приделом границ" << std::endl;
    }
}

void clear(MyStack<PrintedEdition*>& stack) {
    if (stack.any()) {
        std::cout << "Контейнер уже пуст" << std::endl;
        return;
    }

    while (!stack.any()) {
        PrintedEdition* item = stack.get();
        delete item;
        stack.pop();
    }

    std::cout << "Контейнер успешно очищен" << std::endl;
}

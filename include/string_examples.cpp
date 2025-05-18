#include "string_examples.h"
#include <iostream>
#include <string>
#include <fstream>

void runStringExamples() {
    // Запускаем примеры работы со строками
    swapFirstLetters();
    duplicateEqualsAndRemoveSpaces();
    replaceDigitsWithAsterisk();
}

// Задание 1: Переставить первую букву первого предложения и первую букву последнего предложения
void swapFirstLetters() {
    std::cout << "\nЗадание 1: Переставить первую букву первого предложения и первую букву последнего предложения\n";

    std::string text;
    std::cout << "Введите текст: ";
    std::getline(std::cin, text);

    // Находим индекс первой буквы первого предложения
    size_t firstLetterIndex = 0;
    while (firstLetterIndex < text.length() && !std::isalpha(text[firstLetterIndex])) {
        firstLetterIndex++;
    }

    if (firstLetterIndex >= text.length()) {
        std::cout << "В тексте нет букв." << std::endl;
        return;
    }

    // Находим индекс последней точки (исключая последнюю точку в конце текста)
    size_t lastDotIndex = text.rfind('.');
    if (lastDotIndex == std::string::npos || lastDotIndex == text.length() - 1) {
        // Если точки нет или это последняя точка в конце текста, ищем предпоследнюю
        lastDotIndex = text.rfind('.', text.length() - 2);
    }

    if (lastDotIndex == std::string::npos) {
        std::cout << "В тексте нет точек или есть только одна точка в конце." << std::endl;
        return;
    }

    // Находим индекс первой буквы последнего предложения
    size_t lastSentenceFirstLetterIndex = lastDotIndex + 1;
    while (lastSentenceFirstLetterIndex < text.length() && !std::isalpha(text[lastSentenceFirstLetterIndex])) {
        lastSentenceFirstLetterIndex++;
    }

    if (lastSentenceFirstLetterIndex >= text.length()) {
        std::cout << "В последнем предложении нет букв." << std::endl;
        return;
    }

    // Меняем местами первые буквы
    char temp = text[firstLetterIndex];
    text[firstLetterIndex] = text[lastSentenceFirstLetterIndex];
    text[lastSentenceFirstLetterIndex] = temp;

    std::cout << "Результат: " << text << std::endl;
}

// Задание 2: Удвоить каждый символ "=" и пропустить пробелы
void duplicateEqualsAndRemoveSpaces() {
    std::cout << "\nЗадание 2: Удвоить каждый символ '=' и пропустить пробелы\n";

    std::string input;
    std::cout << "Введите последовательность символов: ";
    std::getline(std::cin, input);

    std::string result;
    for (char c : input) {
        if (c == '=') {
            result += "=="; // Удваиваем символ "="
        } else if (c != ' ') { // Пропускаем пробелы
            result += c;
        }
    }

    std::cout << "Результат: " << result << std::endl;
}

// Задание 3: Заменить все цифры на "*" в файле
void replaceDigitsWithAsterisk() {
    std::cout << "\nЗадание 3: Заменить все цифры на '*' в файле\n";

    // Создаем первый файл для демонстрации
    std::ofstream inputFile("input.txt");
    if (inputFile.is_open()) {
        inputFile << "Пример текста с цифрами: 123, абв456, 7д8е9ж." << std::endl;
        inputFile.close();
        std::cout << "Файл input.txt создан." << std::endl;
    } else {
        std::cout << "Не удалось создать файл input.txt." << std::endl;
        return;
    }

    // Открываем файл для чтения
    std::ifstream inFile("input.txt");
    if (!inFile.is_open()) {
        std::cout << "Не удалось открыть файл input.txt для чтения." << std::endl;
        return;
    }

    // Открываем файл для записи результата
    std::ofstream outFile("output.txt");
    if (!outFile.is_open()) {
        std::cout << "Не удалось открыть файл output.txt для записи." << std::endl;
        inFile.close();
        return;
    }

    std::string line;
    while (std::getline(inFile, line)) {
        for (char& c : line) {
            if (std::isdigit(c)) {
                c = '*';
            }
        }
        outFile << line << std::endl;
    }

    inFile.close();
    outFile.close();

    std::cout << "Результат записан в файл output.txt." << std::endl;

    // Показываем содержимое результата
    std::ifstream resultFile("output.txt");
    if (resultFile.is_open()) {
        std::cout << "Содержимое файла output.txt:" << std::endl;
        while (std::getline(resultFile, line)) {
            std::cout << line << std::endl;
        }
        resultFile.close();
    }
}

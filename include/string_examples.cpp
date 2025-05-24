#include "string_examples.h"
#include <iostream>
#include <string>
#include <fstream>

void runStringExamples() {
    swapFirstLetters();
    duplicateEqualsAndRemoveSpaces();
    replaceDigitsWithAsterisk();
}

void swapFirstLetters() {
    std::cout << "\nЗадание 1: Переставить первую букву первого предложения и первую букву последнего предложения\n";

    std::string text;
    std::cout << "Введите текст: ";
    std::getline(std::cin, text);

    size_t firstLetterIndex = 0;
    while (firstLetterIndex < text.length() && !std::isalpha(text[firstLetterIndex])) {
        firstLetterIndex++;
    }

    if (firstLetterIndex >= text.length()) {
        std::cout << "В тексте нет букв." << std::endl;
        return;
    }

    size_t lastDotIndex = text.rfind('.');
    if (lastDotIndex == std::string::npos || lastDotIndex == text.length() - 1) {
        lastDotIndex = text.rfind('.', text.length() - 2);
    }

    if (lastDotIndex == std::string::npos) {
        std::cout << "В тексте нет точек или есть только одна точка в конце." << std::endl;
        return;
    }

    size_t lastSentenceFirstLetterIndex = lastDotIndex + 1;
    while (lastSentenceFirstLetterIndex < text.length() && !std::isalpha(text[lastSentenceFirstLetterIndex])) {
        lastSentenceFirstLetterIndex++;
    }

    if (lastSentenceFirstLetterIndex >= text.length()) {
        std::cout << "В последнем предложении нет букв." << std::endl;
        return;
    }

    char temp = text[firstLetterIndex];
    text[firstLetterIndex] = text[lastSentenceFirstLetterIndex];
    text[lastSentenceFirstLetterIndex] = temp;

    std::cout << "Результат: " << text << std::endl;
}

void duplicateEqualsAndRemoveSpaces() {
    std::cout << "\nЗадание 2: Удвоить каждый символ '=' и пропустить пробелы\n";

    std::string input;
    std::cout << "Введите последовательность символов: ";
    std::getline(std::cin, input);

    std::string result;
    for (char c : input) {
        if (c == '=') {
            result += "==";
        } else if (c != ' ') {
            result += c;
        }
    }

    std::cout << "Результат: " << result << std::endl;
}

void replaceDigitsWithAsterisk() {
    std::cout << "\nЗадание 3: Заменить все цифры на '*' в файле\n";

    std::ofstream inputFile("input.txt");
    if (inputFile.is_open()) {
        inputFile << "Пример текста с цифрами: 123, абв456, 7д8е9ж." << std::endl;
        inputFile.close();
        std::cout << "Файл input.txt создан." << std::endl;
    } else {
        std::cout << "Не удалось создать файл input.txt." << std::endl;
        return;
    }

    std::ifstream inFile("input.txt");
    if (!inFile.is_open()) {
        std::cout << "Не удалось открыть файл input.txt для чтения." << std::endl;
        return;
    }

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

    std::ifstream resultFile("output.txt");
    if (resultFile.is_open()) {
        std::cout << "Содержимое файла output.txt:" << std::endl;
        while (std::getline(resultFile, line)) {
            std::cout << line << std::endl;
        }
        resultFile.close();
    }
}

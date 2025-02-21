#include "Planet/Planet.h"
#include <iostream>
#include <fstream>
#include <limits>

char menu(){
    std::cout << " ========================= ГЛАВНОЕ МЕНЮ =========================\n";
    std::cout << "|| 1 - чтение БД из файла\t || 5 - удаление объекта из БД ||" << std::endl;
    std::cout << "|| 2 - запись БД в файл\t\t || 6 - редактирование БД      ||" << std::endl;
    std::cout << "|| 3 - сортировка БД\t\t || 7 - вывод БД на экран      ||" << std::endl;
    std::cout << "|| 4 - добавление объекта в БД\t || Любая клавиша - ВЫХОД      ||" << std::endl;
    std::cout << " ================================================================\n";
    std::cout << "Для выбора операции введите цифру от 1 до 7" << std::endl;
    char answer;
    std::cin >> answer;
    return answer;
}

int main(){
    bool exit_programm = true;
    while(exit_programm){
        switch (menu())
        {
        case '1':
            break;

        default:
        std::cout << "Спасибо за работу, до свидания!" << std::endl;
        exit_programm = false;
            break;
        }
    }
}

#include "Planet/Planet.h"
#include "Ticket/Ticket.h"
#include <iostream>
#include <fstream>
#include <limits>
#include <typeinfo>

char menu(){
    std::cout << " ========================= ГЛАВНОЕ МЕНЮ ====================================\n";
    std::cout << "|| 1 - Работа с планетами\t\t\t || 3 - Запуск тестов     ||" << std::endl;
    std::cout << "|| 2 - Работа с железнодорожными билетами\t || Любая клавиша - ВЫХОД ||" << std::endl;
    std::cout << " ===========================================================================\n";
    std::cout << "Для выбора операции введите цифру от 1 до 3" << std::endl;
    char answer;
    std::cin >> answer;
    std::cout << std::endl;
    std::cout << std::endl;
    return answer;
}

char MenuDatabase(){
    std::cout << " ========================= Работа с БД ==========================\n";
    std::cout << "|| 1 - чтение БД из файла\t || 5 - удаление объекта из БД ||" << std::endl;
    std::cout << "|| 2 - запись БД в файл\t\t || 6 - редактирование БД      ||" << std::endl;
    std::cout << "|| 3 - сортировка БД\t\t || 7 - вывод БД на экран      ||" << std::endl;
    std::cout << "|| 4 - добавление объекта в БД\t || Любая клавиша - НАЗАД      ||" << std::endl;
    std::cout << " ================================================================\n";
    std::cout << "Для выбора операции введите цифру от 1 до 7" << std::endl;
    char answer;
    std::cin >> answer;
    std::cout << std::endl;
    std::cout << std::endl;
    return answer;
}

void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

bool Equal(char m1[256], char m2[256]){
    for (int i = 0;  m1[i] != '\0' || m2[i] != '\0'; ++i){
        if (m1[i] != m2[i]){
            return false;
        }
    }
    return true;
}

template<typename T>
void DatabaseFromFile(T* items, int size){
    char filename[256];
    char flag_0[256]{};
    flag_0[0] = '0';
    clearInputBuffer();
    std::cout << "Введите имя файла для чтения или цифру «0» для осведомления с необходимой структурой файла: ";
    std::cin >> filename;
    if (!Equal(filename, flag_0)) {
        //T::readFromFile(filename, items, size);
    } else if (typeid(T) ==typeid(Planet)){
        std::cout << std::endl << "1-я строка: кол-во планет;";
        std::cout << std::endl << "Далее в каждой строчке по одному объекту планеты со следующими характеристиками через пробел:";
        std::cout << std::endl << "1)Название 2)Диаметр 3)Жизнь 4)Спутники" << std::endl;
        std::cout << "\nА теперь введите имя файла для чтения: ";
        std::cin >> filename;
        //T::readFromFile(filename, items, size);
    } else {
        std::cout << std::endl << "1-я строка: кол-во билетов;";
        std::cout << std::endl << "Далее в каждой строчке по одному объекту планеты со следующими характеристиками через пробел:";
        std::cout << std::endl << "1)Рейс(Куда) 2)№Вагона 3)№Места 4)Цена" << std::endl;
        std::cout << "\nА теперь введите имя файла для чтения: ";
        std::cin >> filename;
        //T::readFromFile(filename, items, size);
    }
}

template<typename T>
void DatabaseToFile(T* items, int size){
    char filename[256];
    std::cout << "Введите имя файла для записи: ";
    std::cin >> filename;
    //T::writeToFile(filename, items, size);
}

template<typename T>
void SortDatabase(){

}

template<typename T>
void AddToDatabase(){

}

template<typename T>
void DelFromDatabase(){

}

template<typename T>
void EditDatabase(){

}

template<typename T>
void PrintDatabase(){

}


template<typename T>
void RunDatabase(const std::string& type) {
    T* items = nullptr;
    int size = 0;

    bool exit_run_database = true;
    while(exit_run_database){
        switch (MenuDatabase()){
            case '1':
                DatabaseFromFile<T>(items, size);
                break;
            case '2':
                DatabaseToFile<T>(items, size);
                break;
            case '3':
                SortDatabase<T>();
                break;
            case '4':
                AddToDatabase<T>();
                break;
            case '5':
                DelFromDatabase<T>();
                break;
            case '6':
                EditDatabase<T>();
                break;
            case '7':
                PrintDatabase<T>();
                break;
            default:
                exit_run_database = false;
                break;
        }
    }
}


int main(){
    bool exit_programm = true;
    while(exit_programm){
        switch (menu())
        {
            case '1':
                RunDatabase<Planet>("планет");
                break;
            case '2':
                RunDatabase<Ticket>("билет");
                break;
            case '3':
                break;
            default:
            std::cout << "Спасибо за работу, до свидания!" << std::endl;
            exit_programm = false;
                break;
        }
     clearInputBuffer();
    }
}

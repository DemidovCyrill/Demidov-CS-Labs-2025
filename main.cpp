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
void DatabaseFromFile(T*& items, int& size) {
    char filename[256];
    char flag_0[256]{};
    flag_0[0] = '0';
    clearInputBuffer();
    std::cout << "Введите имя файла для чтения или цифру «0» для осведомления с необходимой структурой файла: ";
    std::cin >> filename;
    if (!Equal(filename, flag_0)) {
        T::readFromFile(filename, items, size);
    } else if (typeid(T) == typeid(Ticket)){
        std::cout << std::endl << "1-я строка: кол-во планет;";
        std::cout << std::endl << "Далее в каждой строчке по одному объекту планеты со следующими характеристиками через пробел:";
        std::cout << std::endl << "1)Название 2)Диаметр 3)Жизнь 4)Спутники" << std::endl;
        std::cout << "\nА теперь введите имя файла для чтения: ";
        std::cin >> filename;
        T::readFromFile(filename, items, size);
    } else {
        std::cout << std::endl << "1-я строка: кол-во билетов;";
        std::cout << std::endl << "Далее в каждой строчке по одному объекту планеты со следующими характеристиками через пробел:";
        std::cout << std::endl << "1)Рейс(Куда) 2)№Вагона 3)№Места 4)Цена" << std::endl;
        std::cout << "\nА теперь введите имя файла для чтения: ";
        std::cin >> filename;
        T::readFromFile(filename, items, size);
    }
}

template<typename T>
void DatabaseToFile(T* items, int size){
    char filename[256];
    std::cout << "Введите имя файла для записи: ";
    std::cin >> filename;
    T::writeToFile(filename, items, size);
}

template<typename T>
void SortDatabase(T*& items, int size){
    T::Sort(items, size);
}

template<typename T>
void AddToDatabase(T*& items, int& size){
    T newItem;
    if constexpr(std::is_same_v<T, Ticket>) {
        std::cout << "Введите данные нового элемента, в одну строку через пробел\n";
        std::cout << "1)Рейс(Куда) 2)№Вагона 3)№Места 4)Цена\n";
        std::cout << "Ваш элемент: ";
    } else {
        std::cout << "Введите данные нового элемента, в одну строку через пробел\n";
        std::cout << "1)Название 2)Диаметр 3)Жизнь 4)Спутники\n";
        std::cout << "Ваш элемент: ";
    }
    std::cin >> newItem;
    T::Add(items, size, newItem);
}

template<typename T>
void DelFromDatabase(T*& items, int& size){
    int index;
    std::cout << "Введите индекс элемента для удаления: ";
    std::cin >> index;
    if (index < 0 || index >= size) {
        std::cerr << "Неверный индекс для удаления!" << std::endl;
        return;
    }
    std::cout << "Вы хотите удалить элемент:\n" << items[index];
    std::cout << "\n(y/n)\n";
    char flag;
    std::cin >> flag;
    if (flag != 'y') {
        DelFromDatabase(items, size);
        return;
    }
    T::Remove(items, size, index);
}

template<typename T>
void EditDatabase(T*& items, int size){
    int index;
    std::cout << "Введите индекс элемента для редактирования: ";
    std::cin >> index;
    if (index < 0 || index >= size) {
        std::cerr << "Неверный индекс для редактирования!" << std::endl;
        return;
    }
    std::cout << "Вы хотите редактированть элемент:\n" << items[index];
    std::cout << "\n(y/n)\n";
    char flag;
    std::cin >> flag;
    if (flag != 'y') {
        EditDatabase(items, size);
        return;
    }
    T::Edit(items, size, index);
}

template<typename T>
void PrintDatabase(T* items, int size){
    T::Print(items, size);
}


template<typename T>
void RunDatabase() {
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
                SortDatabase<T>(items, size);
                break;
            case '4':
                AddToDatabase<T>(items, size);
                break;
            case '5':
                DelFromDatabase<T>(items, size);
                break;
            case '6':
                EditDatabase<T>(items, size);
                break;
            case '7':
                PrintDatabase<T>(items, size);
                break;
            default:
                exit_run_database = false;
                break;
        }
    }
}

//std::cout << "" << std::endl;
void RunTests(){
    std::cout << "В этом режиме будут протестированны функции программы" << std::endl;
    std::cout << "Если вы будете неудовлетворены результатом, то можете протестировать в ручном режиме!" << std::endl;
    std::cout << std::endl << "Тестировка работы БД планет:" << std::endl;
    Planet* items = nullptr;
    int size = 0;

    std::cout << "Добавление Нептуна, Юпитера, Марса, солнца, астероида и землии соответсвенно (с их характеристиками)" << std::endl;
    std::cout << "Формат: 1)Название 2)Диаметр 3)Жизнь 4)Спутники\n" << std::endl;
    Planet::Add(items, size, Planet("Neptune", 49600, 0, 14));
    Planet::Add(items, size, Planet("Jupiter", 142796, 0, 79));
    Planet::Add(items, size, Planet("Mars", 6786, 1, 2));
    Planet::Add(items, size, Planet("Sun", 1392000, 0, 13));
    Planet::Add(items, size, Planet("Asteroid", 1, 0, 0));
    Planet::Add(items, size, Planet("Earth", 12756, 1, 1));
    PrintDatabase<Planet>(items, size);

    std::cout << std::endl << "Сортировка Элементов:" << std::endl;
    SortDatabase<Planet>(items, size);
    PrintDatabase<Planet>(items, size);

    std::cout << std::endl << "Удаления солнца и нептуна (они мне не нравятся):" << std::endl;
    Planet::Remove(items, size, 3);
    Planet::Remove(items, size, 4);
    PrintDatabase<Planet>(items, size);

    std::cout << std::endl << "Изменение элементов (увеличение астероида и вымирание человечества):" << std::endl;
    items[0] = Planet("Asteroid", 10000, 0, 0);
    items[2] = Planet("Earth", 12756, 0, 1);
    PrintDatabase<Planet>(items, size);

    std::cout << std::endl << "Сортировка Элементов:" << std::endl;
    SortDatabase<Planet>(items, size);
    PrintDatabase<Planet>(items, size);

    std::cout << std::endl << "Вывод БД в файл test_planet.txt в данную директорию:" << std::endl;
    Planet::writeToFile("test_planet.txt", items, size);
}


int main(){
    bool exit_programm = true;
    while(exit_programm){
        switch (menu())
        {
            case '1':
                RunDatabase<Planet>();
                break;
            case '2':
                RunDatabase<Ticket>();
                break;
            case '3':
            RunTests();
                break;
            default:
            std::cout << "Спасибо за работу, до свидания!" << std::endl;
            exit_programm = false;
                break;
        }
     clearInputBuffer();
    }
}

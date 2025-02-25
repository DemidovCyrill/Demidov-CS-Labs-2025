#include "Planet.h"
#include <cstring>
#include <algorithm>
#include <fstream>

Planet::Planet() : name(nullptr), diameter(0), hasLife(false), satellites(0) {
}

Planet::Planet(const char* name, long long diameter, bool hasLife, int satellites)
    : diameter(diameter), hasLife(hasLife), satellites(satellites) {
    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);
}

// Planet::Planet(const Planet& other) : name(nullptr) {
//     copyFrom(other);
// }

Planet::~Planet() {
    cleanup();
}

// bool Planet::operator<(const Planet& other) const {
//     return diameter < other.diameter;
// }

// bool Planet::operator==(const Planet& other) const {
//     return diameter == other.diameter;
// }

std::ostream& operator<<(std::ostream& os, const Planet& planet) {
    os << planet.name << " " << planet.diameter << " " << planet.hasLife << " " << planet.satellites;
    return os;
}

std::istream& operator>>(std::istream& is, Planet& planet) {
    char name[256];
    is >> name;
    delete[] planet.name;
    planet.name = new char[strlen(name) + 1];
    strcpy(planet.name, name);

    is >> planet.diameter >> planet.satellites >> planet.hasLife;
    return is;
}

void Planet::readFromFile(const char* filename, Planet*& planets, int& size) {
    std::ifstream file(filename);
    if (!file) {
        std::cout << "!!!ОШИБКА!!!" << std::endl << "Не удалось открыть файл!" << std::endl;
        return;
    }

    file >> size;
    file.ignore();
    std::cout << "УСПЕШНО!";
    std::cout << std::endl << "Хотите проверить полученную информацию? (y/n): ";
    char flag;
    char error_flag = false;
    std::cin >> flag;
    if (flag == 'y') {
        std::cout << "Прочитан размер: " << size << std::endl;
    }

    if (planets != nullptr) {
        delete[] planets;
        planets = nullptr;
    }

    planets = new Planet[size];

    for (int i = 0; i < size; i++) {
        char name[256];
        long long diam;
        int life;
        int sat;

        if (file >> name >> diam >> life >> sat) {
            if (flag == 'y') {
                std::cout << "Попытка создания планеты " << i << ": "
                      << name << " " << diam << " "
                      << sat << " " << life << std::endl;
            }

            planets[i] = Planet(name, diam, sat, life != 0);
            if (flag == 'y') {
                std::cout << "Планета " << i << " успешно создана" << std::endl;
            } else {
                std::cout << "Ошибка при чтении планеты " << i << std::endl;
                error_flag = true;
                break;
            }
        }
    }
    if (error_flag & (flag != 'y')) {std::cout << "Была некая ошибка при чтении планеты!";}
    file.close();
}

void Planet::writeToFile(const char* filename, const Planet* planets, int size) {
    std::ofstream file(filename);
    if (!file) {
        std::cerr << "Не удалось открыть файл для записи." << std::endl;
        return;
    }

    file << size << std::endl;
    for (int i = 0; i < size; ++i) {
        file << planets[i] << std::endl;
    }

    file.close();
}

void Planet::sortPlanets(Planet* planets, int size) {
    std::sort(planets, planets + size);
}

void Planet::addPlanet(Planet*& planets, int& size, const Planet& newPlanet) {
    Planet* newArray = new Planet[size + 1];
    for (int i = 0; i < size; ++i) {
        newArray[i] = planets[i];
    }
    newArray[size] = newPlanet;
    delete[] planets;
    planets = newArray;
    ++size;
}

void Planet::removePlanet(Planet*& planets, int& size, int index) {
    if (index < 0 || index >= size) {
        std::cerr << "Неверный индекс для удаления." << std::endl;
        return;
    }

    Planet* newArray = new Planet[size - 1];
    int j = 0;
    for (int i = 0; i < size; ++i) {
        if (i != index) {
            newArray[j++] = planets[i];
        }
    }
    delete[] planets;
    planets = newArray;
    --size;
}

void Planet::editPlanet(Planet& planet) {
    std::cout << "Введите новые данные для планеты:" << std::endl;
    std::cin >> planet;
}

void Planet::displayPlanets(const Planet* planets, int size) {
    for (int i = 0; i < size; ++i) {
        std::cout << planets[i] << std::endl;
    }
}


void Planet::copyFrom(const Planet& other) {
    if (other.name) {
        name = new char[strlen(other.name) + 1];
        strcpy(name, other.name);
    } else {
        name = nullptr;
    }
    diameter = other.diameter;
    satellites = other.satellites;
    hasLife = other.hasLife;
}

void Planet::cleanup() {
    delete[] name;
    name = nullptr;
}

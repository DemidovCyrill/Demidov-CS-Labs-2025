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

Planet::Planet(const Planet& other) : name(nullptr) {
    Copy(other);
}

Planet::~Planet() {
    cleanup();
}


Planet& Planet::operator=(const Planet& other) {
    if (this != &other) {
        cleanup();
        Copy(other);
    }
    return *this;
}

bool Planet::operator<(const Planet& other) const {
    return std::strcmp(name, other.name) < 0;
}



bool Planet::operator==(const Planet& other) const {
    return std::strcmp(name, other.name) == 0;
}


std::istream& operator>>(std::istream& is, Planet& planet) {
    char name[256];
    is >> name;
    delete[] planet.name;
    planet.name = new char[strlen(name) + 1];
    strcpy(planet.name, name);
    is >> planet.diameter >> planet.hasLife >> planet.satellites;
    return is;
}

std::ofstream& operator<<(std::ofstream& os, const Planet& planet) {
    os << planet.name << " " << planet.diameter << " " << planet.hasLife << " " << planet.satellites;
    return os;
}


std::ostream& operator<<(std::ostream& os, const Planet& planet) {
    os << planet.name << " " << planet.diameter << " " << planet.hasLife << " " << planet.satellites;
    return os;
}

std::ifstream& operator>>(std::ifstream& is, Planet& planet) {
    char name[256];
    is >> name;
    delete[] planet.name;
    planet.name = new char[strlen(name) + 1];
    strcpy(planet.name, name);
    is >> planet.diameter >> planet.hasLife >> planet.satellites;
    return is;
}

void Planet::readFromFile(const char* filename, Planet*& planets, int& size) {
    std::ifstream file(filename);
    if (!file) {
        std::cout << "!!!ОШИБКА!!!" << std::endl << "Не удалось открыть файл!" << std::endl;
        return;
    }

    int newSize;
    file >> newSize;
    if (newSize <= 0) {
        std::cout << "Некорректный размер в файле!" << std::endl;
        file.close();
        return;
    }

    file.ignore();
    std::cout << "УСПЕШНО!" << std::endl;

    Planet* newPlanets = new Planet[newSize];
    bool success = true;

    for (int i = 0; i < newSize; i++) {
        char name[256];
        long long diam;
        int life;
        int sat;

        if (file >> name >> diam >> life >> sat) {
            newPlanets[i] = Planet(name, diam, life != 0, sat);
        } else {
            std::cerr << "Ошибка при чтении планеты " << i << std::endl;
            success = false;
            break;
        }
    }

    file.close();

    if (success) {
        if (planets != nullptr) {
            delete[] planets;
        }
        planets = newPlanets;
        size = newSize;
    } else {
        delete[] newPlanets;
        std::cout << "Произошла ошибка при чтении файла" << std::endl;
    }
}



void Planet::writeToFile(const char* filename, const Planet* planets, int size) {
    std::ofstream file(filename);
    if (!file) {
        std::cerr << "Не удалось открыть файл для записи." << std::endl;
        return;
    }
    std::cout << "Производится запись в файл." << std::endl;
    file << size << std::endl;
    for (int i = 0; i < size; i = i + 1) {
        std::cout << planets[i] << std::endl;
        file << planets[i] << std::endl;
    }
    file.close();
    std::cout << "Успешно!" << std::endl;
}

void swap(Planet& a, Planet& b)
{
    Planet c = a;
    a = b;
    b = c;

}

void Planet::Sort(Planet* planets, int size) {
    bool swapped;
    for (size_t i = 0; i < size; ++i)
    {
        swapped = false;
        for (size_t j = 0; j < size - i - 1; ++j)
        {
            if (planets[j + 1] < planets[j]) {
                swap(planets[j], planets[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) {
            break;
        }
    }
}

void Planet::Add(Planet*& planets, int& size, const Planet& newPlanet) {
    Planet* newArray = new Planet[size + 1];
    for (int i = 0; i < size; ++i) {
        newArray[i] = planets[i];
    }
    newArray[size] = newPlanet;
    delete[] planets;
    planets = newArray;
    ++size;
}

void Planet::Remove(Planet*& planets, int& size, int index) {
    Planet* newArray = new Planet[size - 1];
    int j = 0;
    for (int i = 0; i < size; ++i) {
        if (i != index) {
            newArray[j++] = planets[i];
        }
    }
        delete planets[index].name;
    delete[] planets;
    planets = newArray;
    --size;
}

void Planet::Edit(Planet*& planets, int size, int index) {
    Planet planet;
    std::cout << "Введите новые данные для планеты (должны быть заполнены все 4 поля):" << std::endl;
    std::cin >> planet;
    planets[index] = planet;
}

void Planet::Print(const Planet* planets, int size) {
    std::cout << "Количество планет: " << size << std::endl;
    for (int i = 0; i < size; ++i) {
        std::cout << planets[i] << std::endl;
    }
}


void Planet::Copy(const Planet& other) {
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

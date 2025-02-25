#ifndef PLANET_H
#define PLANET_H
#include <iostream>

class Planet {
private:
    static int count;
    int id;
    char* name;
    long long diameter;
    int satellites;
    bool hasLife;

public:
    Planet();
    Planet(const char* name, long long diameter, bool hasLife, int satellites);
    Planet(const Planet& other);
    ~Planet();


    Planet& operator=(const Planet& other);
    bool operator<(const Planet& other) const;
    bool operator==(const Planet& other) const;

    friend std::istream& operator>>(std::istream& is, Planet& planet);
    friend std::ostream& operator<<(std::ostream& os, const Planet& planet);
    friend std::ofstream& operator<<(std::ofstream& os, const Planet& planet);
    friend std::ifstream& operator>>(std::ifstream& is, Planet& planet);

    static void readFromFile(const char* filename, Planet*& planets, int& size);
    static void writeToFile(const char* filename, const Planet* planets, int size);
    static void Sort(Planet* planets, int size);
    static void Add(Planet*& planets, int& size, const Planet& newPlanet);
    static void Remove(Planet*& planets, int& size, int index);
    static void Edit(Planet& planet);
    static void Print(const Planet* planets, int size);

private:
    void Copy(const Planet& other);
    void cleanup();
};

#endif // PLANET_H

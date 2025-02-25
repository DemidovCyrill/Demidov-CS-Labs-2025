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

    friend std::ostream& operator<<(std::ostream& os, const Planet& planet);
    friend std::istream& operator>>(std::istream& is, Planet& planet);

    static void readFromFile(const char* filename, Planet*& planets, int& size);
    static void writeToFile(const char* filename, const Planet* planets, int size);
    static void sortPlanets(Planet* planets, int size);
    static void addPlanet(Planet*& planets, int& size, const Planet& newPlanet);
    static void removePlanet(Planet*& planets, int& size, int index);
    static void editPlanet(Planet& planet);
    static void displayPlanets(const Planet* planets, int size);

private:
    void copyFrom(const Planet& other);
    void cleanup();
};

#endif // PLANET_H

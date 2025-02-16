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
    Planet(const char* name, long long diameter, int satellites, bool hasLife);
    Planet(const Planet& other);
    ~Planet();
};

#endif // PLANET_H

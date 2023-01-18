#include "Material.h"
#include <map>

#pragma once
class Building {
public:
    char getLabel();
    double getNetCost();
    std::map<Material, int>& getNeededMaterial();
    std::map<Material, int> neededMaterial;

protected:
    char label;
    double netCost = 10000;
};

class EmptySpace : public Building {
public:
    EmptySpace();
};

class WindPlant : public Building {
public:
    WindPlant();
};

class HydroPlant : public Building {
public:
    HydroPlant();
};

class SolarPlant : public Building {
public:
    SolarPlant();
};
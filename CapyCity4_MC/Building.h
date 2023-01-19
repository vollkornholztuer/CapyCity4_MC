#include "Material.h"
#include <map>

#pragma once
class Building {
public:
    char getLabel();
    double getNetCost();
    double getMaterialCost();
    double getBuildingPrice();
    double getWattage();
    std::map<Material, int>& getNeededMaterial();
    std::map<Material, int> neededMaterial;

protected:
    double wattageMW; // Leistung
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
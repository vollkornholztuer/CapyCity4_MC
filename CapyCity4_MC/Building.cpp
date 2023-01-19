#include "Building.h"
#include "Material.h"
#include <map>

char label;

//Building::Building() : neededMaterial() {};

EmptySpace::EmptySpace() {
	double netCost = 0;
	this->label = 'E';
}

WindPlant::WindPlant() {
	neededMaterial = std::map<Material, int>({
		{Wood(), 2},
		{Metal(), 1},
		{Plastic(), 4}
		});
	this->label = 'W';
	this->wattageMW = 5.0;
}

HydroPlant::HydroPlant() {
	neededMaterial = std::map<Material, int>({
		{Wood(), 5},
		{Metal(), 2}
		});
	this->label = 'H';
	this->wattageMW = 1.8;
}

SolarPlant::SolarPlant() {
	neededMaterial = std::map<Material, int>({
		{Plastic(), 2},
		{Metal(), 5}
		});
	this->label = 'S';
	this->wattageMW = 2.5;
}

char Building::getLabel() {
	return label;
}

double Building::getNetCost() {
	return netCost;
}

double Building::getMaterialCost() {
	double mat = 0;
	for (auto& it : neededMaterial) {
		mat += it.first.getMaterialPrice() * it.second;
	}
	return mat;
}

double Building::getBuildingPrice() {
	return netCost + getMaterialCost();
}

std::map<Material, int>& Building::getNeededMaterial() {
	return neededMaterial;
}

// TODO: Leistung / Wattage
double Building::getWattage() {
	return wattageMW;
}
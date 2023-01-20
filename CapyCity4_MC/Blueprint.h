#pragma once
#include <string>
#include "Building.h"

class Blueprint {
public:
	Blueprint() {
		declareBuildingArea();
	}
	Building** buildArea;
	bool running = true;
	double kennZahl = 0;

	void declareBuildingArea();

	void build();
	Building* chooseBuildingType();
	int inputBuildingWidth(int xCoordinate);
	int inputBuildingLength(int yCoordinate);
	int inputBuildingXCoordinate();
	int inputBuildingYCoordinate();
	bool checkBuilding(int xCoordinate, int yCoordinate, int buildingLength, int buildingHeight);
	void setBuilding(Building* building, int xCoordinate, int yCoordinate, int buildingLength, int buildingWidth);

	void destroy();
	void showBuildArea();
	std::string toString();
	void setKennzahl();
	double getKennzahl();

	bool operator()(Building** a, Building** b);
};
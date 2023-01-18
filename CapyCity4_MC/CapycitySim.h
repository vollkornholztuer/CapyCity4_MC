#pragma once
using namespace std;

#include "Building.h"

class CapycitySim
{
public:
	Building** buildArea;
	int width;
	int length;
	bool running = true;

	void menu();
	void declareBuildingArea(int buildAreaWidth, int buildAreaLength);

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
};
#include "CapycitySim.h"
#include "Building.h"
#include "Material.h"
#include <iostream>
#include <regex>

regex menuCheck("[1-4]");
regex numberCheck("[[:digit:]]+");

void CapycitySim::declareBuildingArea(int buildAreaWidth, int buildAreaLength) {
    buildArea = new Building * [buildAreaWidth];
    for (int x = 0; x < buildAreaWidth; x++) {
        buildArea[x] = new Building[buildAreaLength];
        for (int y = 0; y < buildAreaLength; y++) {
            buildArea[x][y] = EmptySpace::EmptySpace();
        }
    }
    width = buildAreaWidth;
    length = buildAreaLength;
}

void CapycitySim::menu()
{
    std::string input;
    std::cout << "*********** MENU ***********" << std::endl;
    std::cout << "Gebaeude bauen (1)" << std::endl;
    std::cout << "Gebaeude abreissen (2)" << std::endl;
    std::cout << "Bauplan ausgeben (3)" << std::endl;
    std::cout << "Programm beenden (4)" << std::endl;
    std::cout << "Eingabe: ";
    std::cin >> input;
    std::cout << "****************************" << std::endl;
    if (regex_match(input, menuCheck)) {
        switch (stoi(input)) {
        case 1:
            build();
            break;
        case 2:
            destroy();
            break;
        case 3:
            showBuildArea();
            break;
        case 4:
            exit(0);
            running = false;
            break;
        default:
            break;
        }
    }
    else {
        std::cout << "Ungueltige Eingabe\n";
    }
}

void CapycitySim::build()
{
    Building* building = chooseBuildingType();
    int xCoordinate = inputBuildingXCoordinate();
    int yCoordinate = inputBuildingYCoordinate();
    int buildingWidth = inputBuildingWidth(xCoordinate);
    int buildingLength = inputBuildingLength(yCoordinate);
    bool buildSpaceAlreadyInUse = checkBuilding(xCoordinate, yCoordinate, buildingLength, buildingWidth);
    if (buildSpaceAlreadyInUse) {
        std::cout << "Du kannst hier nicht Bauen. Der Platz ist schon belegt.\n";
    }
    else {
        setBuilding(building, xCoordinate, yCoordinate, buildingLength, buildingWidth);
    }
}

Building* CapycitySim::chooseBuildingType()
{
    std::string input;

    std::cout << "1 - Wasserkraft\n";
    std::cout << "2 - Windkraft\n";
    std::cout << "3 - Solarkraft\n";
    std::cout << "Gebaeudetyp waehlen: ";
    std::cin >> input;

    if (regex_match(input, menuCheck)) {
        switch (stoi(input)) {
        case 1:
            return new HydroPlant(); // Wasserkraft
            break;
        case 2:
            return new WindPlant(); // Windkraft
            break;
        case 3:
            return new SolarPlant(); // Solarkraft
            break;
        default:
            break;
        }
    }
    else {
        std::cout << "Ungueltige Eingabe!\n";
    }
    return nullptr;
}

int CapycitySim::inputBuildingWidth(int xCoordinate)
{
    std::string input;
    std::cout << "Gebaeudebreite eingeben: ";
    std::cin >> input;

    if (regex_match(input, numberCheck) && stoi(input) > 0 && (xCoordinate + stoi(input) - 1) < width) {
        return stoi(input);
    }
    else {
        std::cout << "Ungültige Eingabe\n";
        return inputBuildingWidth(xCoordinate);
    }

}

int CapycitySim::inputBuildingLength(int yCoordinate)
{
    std::string input;
    std::cout << "Gebaeudelaenge eingeben: ";
    std::cin >> input;

    if (regex_match(input, numberCheck) && stoi(input) > 0 && (yCoordinate + stoi(input) - 1) < length) {
        return stoi(input);
    }
    else {
        std::cout << "Gebaeude zu gross\n";
        return inputBuildingLength(yCoordinate);
    }
}

int CapycitySim::inputBuildingXCoordinate()
{
    std::string input;
    std::cout << "x-Koordinate fuer Gebaeude eingeben: ";
    std::cin >> input;

    if (regex_match(input, numberCheck) && (stoi(input) >= 0 && stoi(input) < width)) {
        return stoi(input);
    }
    else {
        cout << "Eingabe ungueltig" << endl;
        return inputBuildingXCoordinate();
    }
}

int CapycitySim::inputBuildingYCoordinate()
{
    std::string input;
    std::cout << "y-Koordinate fuer Gebaeude eingeben: ";
    std::cin >> input;

    if (regex_match(input, numberCheck) && (stoi(input) >= 0 && stoi(input) < length)) {
        return stoi(input);
    }
    else {
        std::cout << "Eingabe ungültig" << endl;
        return inputBuildingYCoordinate();
    }
}

bool CapycitySim::checkBuilding(int xCoordinate, int yCoordinate, int buildingLength, int buildingWidth)
{
    bool alreadyBuilt = false;
    for (int i = xCoordinate; i < buildingWidth + xCoordinate; i++) {
        for (int j = yCoordinate; j < buildingLength + yCoordinate; j++) {
            if (buildArea[i][j].getLabel() != 'E') {
                alreadyBuilt = true;
            }
        }
    }
    return alreadyBuilt;
}

void CapycitySim::setBuilding(Building* building, int xCoordinate, int yCoordinate, int buildingLength, int buildingWidth)

{
    for (int i = xCoordinate; i < buildingWidth + xCoordinate; i++) {
        for (int j = yCoordinate; j < buildingLength + yCoordinate; j++) {
            buildArea[i][j] = *building;
        }
    }
}

void CapycitySim::destroy()
{
    int xCoordinate = inputBuildingXCoordinate();
    int yCoordinate = inputBuildingYCoordinate();
    if (buildArea[xCoordinate][yCoordinate].getLabel() == 'E') {
        std::cout << "An den Koordinaten x=" << xCoordinate << ", y=" << yCoordinate << " ist nichts gebaut.\n";
    }
    else {
        buildArea[xCoordinate][yCoordinate] = EmptySpace();
        std::cout << "Gebaeude an den Koordinaten x=" << xCoordinate << " y=" << yCoordinate << " wurde abgerissen.\n\n";
    }
}

void CapycitySim::showBuildArea()
{
    int countWindPlant = 0;
    int countHydroPlant = 0;
    int countSolarPlant = 0;

    int countWood = 0;
    int countMetal = 0;
    int countPlastic = 0;

    /*Material** materials;*/ // evtl. nicht mehr gebraucht
    double totalCost = 0;

    for (int i = 0; i < length; i++) {
        for (int j = 0; j < width; j++) {
            char type = buildArea[j][i].getLabel();
            if (type == 'E') {
                std::cout << ".";
            }
            else if (type == 'H') { // HydroPlant
                std::cout << type;
                countHydroPlant += 1;
            }
            else if (type == 'W') { // WindPlant
                std::cout << type;
                countWindPlant += 1;
            }
            else if (type == 'S') { // SolarPlant
                std::cout << type;
                countSolarPlant += 1;
            }
        }
        std::cout << "\n";
    }
    // TODO: output prices

    // Berechnung Kosten
    HydroPlant hydroPlant;
    WindPlant windPlant;
    SolarPlant solarPlant;
    std::map<Material, int>& hydroMaterials = HydroPlant().getNeededMaterial();
    std::map<Material, int>& windMaterials = WindPlant().getNeededMaterial();
    std::map<Material, int>& solarMaterials = SolarPlant().getNeededMaterial();
    std::map<Material, int>::iterator it;

    double hydroMaterialCost = 0;
    for (auto& it : hydroPlant.neededMaterial) {
        hydroMaterialCost += it.first.getMaterialPrice() * it.second;
    }

    double windMaterialCost = 0;
    for (auto& it : hydroPlant.neededMaterial) {
        windMaterialCost += it.first.getMaterialPrice() + it.second;
    }

    double solarMaterialCost = 0;
    for (auto& it : hydroPlant.neededMaterial) {
        solarMaterialCost += it.first.getMaterialPrice() * it.second;
    }

    double hydroCost = countHydroPlant * (hydroMaterialCost + HydroPlant().getNetCost());
    double windCost = countWindPlant * (windMaterialCost + WindPlant().getNetCost());
    double solarCost = countSolarPlant * (solarMaterialCost + WindPlant().getNetCost());

    std::cout << "Es befinden sich " << countHydroPlant << " Wasserkraftwerke im Baugebiet\n";
    std::cout << "Die Materialkosten dafuer betragen: " << hydroMaterialCost * countHydroPlant << "\n";
    std::cout << "Die Gesamtkosten der Wasserkraftanlagen betragen: " << hydroCost << "\n\n";

    std::cout << "Es befinden sich " << countWindPlant << " Windkraftwerke im Baugebiet\n";
    std::cout << "Die Materialkosten dafuer betragen: " << windMaterialCost * countWindPlant << "\n";
    std::cout << "Die Gesamtkosten der Windkraftanlagen betragen: " << windCost << "\n\n";

    std::cout << "Es befinden sich " << countSolarPlant << " Solarkraftwerke im Baugebiet\n";
    std::cout << "Die Materialkosten dafuer betragen: " << solarMaterialCost * countSolarPlant << "\n";
    std::cout << "Die Gesamtkosten der Solarkraftanlagen betragen: " << solarCost << "\n\n";
}
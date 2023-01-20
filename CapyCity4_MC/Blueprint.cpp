#include "Blueprint.h"
#include "CapycitySim.h"
#include "Building.h"
#include "Material.h"
#include "CapyCity4_MC.h"
#include <iostream>

void Blueprint::declareBuildingArea()
{
    buildArea = new Building * [width];
    for (int x = 0; x < width; x++) {
        buildArea[x] = new Building[length];
        for (int y = 0; y < length; y++) {
            buildArea[x][y] = EmptySpace::EmptySpace();
        }
    }
}

void Blueprint::build()
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
        setKennzahl();
    }
}

Building* Blueprint::chooseBuildingType()
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

int Blueprint::inputBuildingWidth(int xCoordinate)
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

int Blueprint::inputBuildingLength(int yCoordinate)
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

int Blueprint::inputBuildingXCoordinate()
{
    std::string input;
    std::cout << "x-Koordinate fuer Gebaeude eingeben: ";
    std::cin >> input;

    if (regex_match(input, numberCheck) && (stoi(input) >= 0 && stoi(input) < width)) {
        return stoi(input);
    }
    else {
        std::cout << "Eingabe ungueltig" << std::endl;
        return inputBuildingXCoordinate();
    }
}

int Blueprint::inputBuildingYCoordinate()
{
    std::string input;
    std::cout << "y-Koordinate fuer Gebaeude eingeben: ";
    std::cin >> input;

    if (regex_match(input, numberCheck) && (stoi(input) >= 0 && stoi(input) < length)) {
        return stoi(input);
    }
    else {
        std::cout << "Eingabe ungültig" << std::endl;
        return inputBuildingYCoordinate();
    }
}

bool Blueprint::checkBuilding(int xCoordinate, int yCoordinate, int buildingLength, int buildingWidth)
{
    bool alreadyBuilt = false;
    /*for (int i = xCoordinate; i < buildingWidth + xCoordinate; i++) {
        for (int j = yCoordinate; j < buildingLength + yCoordinate; j++) {
            if (buildArea[j][i].getLabel() != 'E') {
                alreadyBuilt = true;
            }
        }
    }*/
    for (int i = yCoordinate; i < buildingLength + yCoordinate; i++) {
        for (int j = xCoordinate; j < buildingWidth + xCoordinate; j++) {
            if (buildArea[j][i].getLabel() != 'E') {
                alreadyBuilt = true;
            }
        }
    }
    return alreadyBuilt;
}

void Blueprint::setBuilding(Building* building, int xCoordinate, int yCoordinate, int buildingLength, int buildingWidth)
{
    /*for (int i = xCoordinate; i < buildingWidth + xCoordinate; i++) {
        for (int j = yCoordinate; j < buildingLength + yCoordinate; j++) {
            buildArea[i][j] = *building;
        }
    }*/

    for (int i = yCoordinate; i < buildingLength + yCoordinate; i++) {
        for (int j = xCoordinate; j < buildingWidth + xCoordinate; j++) {
            buildArea[j][i] = *building;
        }
    }
}

void Blueprint::destroy()
{
    int xCoordinate = inputBuildingXCoordinate();
    int yCoordinate = inputBuildingYCoordinate();
    if (buildArea[xCoordinate][yCoordinate].getLabel() == 'E') {
        std::cout << "An den Koordinaten x=" << xCoordinate << ", y=" << yCoordinate << " ist nichts gebaut.\n";
    }
    else {
        buildArea[xCoordinate][yCoordinate] = EmptySpace();
        setKennzahl();
        std::cout << "Gebaeude an den Koordinaten x=" << xCoordinate << " y=" << yCoordinate << " wurde abgerissen.\n\n";
    }
}

void Blueprint::showBuildArea()
{
    int countWindPlant = 0;
    int countHydroPlant = 0;
    int countSolarPlant = 0;

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

    // Berechnung Kosten
    HydroPlant hydroPlant;
    WindPlant windPlant;
    SolarPlant solarPlant;

    double hydroMaterialCost = hydroPlant.getMaterialCost();
    double hydroPlantCost = hydroMaterialCost + hydroPlant.getNetCost();
    double hydroCost = hydroPlantCost * countHydroPlant;
    double hydroWattage = countHydroPlant * hydroPlant.getWattage();

    double windMaterialCost = windPlant.getMaterialCost();
    double windPlantCost = windMaterialCost + windPlant.getNetCost();
    double windCost = windPlantCost * countWindPlant;
    double windWattage = countWindPlant * windPlant.getWattage();

    double solarMaterialCost = solarPlant.getMaterialCost();
    double solarPlantCost = solarMaterialCost + solarPlant.getNetCost();
    double solarCost = solarPlantCost * countSolarPlant;
    double solarWattage = countSolarPlant * solarPlant.getWattage();

    double totalCost = hydroCost + windCost + solarCost;
    double totalWattage = hydroWattage + windWattage + solarWattage;

    std::cout << "Es befinden sich " << countHydroPlant << " Wasserkraftwerke im Baugebiet\n";
    std::cout << "Die Materialkosten dafuer betragen: " << hydroMaterialCost * countHydroPlant << "\n";
    std::cout << "Die Gesamtkosten der Wasserkraftanlagen betragen: " << hydroCost << "\n";
    std::cout << "Die Wasserkraftanlagen erbringen einen Stromertrag von " << hydroWattage << " MW\n\n";

    std::cout << "Es befinden sich " << countWindPlant << " Windkraftwerke im Baugebiet\n";
    std::cout << "Die Materialkosten dafuer betragen: " << windMaterialCost * countWindPlant << "\n";
    std::cout << "Die Gesamtkosten der Windkraftanlagen betragen: " << windCost << "\n";
    std::cout << "Die Windkraftanlagen erbringen einen Stromertrag von " << windWattage << " MW\n\n";

    std::cout << "Es befinden sich " << countSolarPlant << " Solarkraftwerke im Baugebiet\n";
    std::cout << "Die Materialkosten dafuer betragen: " << solarMaterialCost * countSolarPlant << "\n";
    std::cout << "Die Gesamtkosten der Solarkraftanlagen betragen: " << solarCost << "\n";
    std::cout << "Die Solarkraftanlagen erbringen einen Stromertrag von " << solarWattage << " MW\n\n";

    std::cout << "Die Gesamtkosten betragen " << totalCost << "\n";
    std::cout << "Die Gesamtleistung der Kraftwerke beträgt " << totalWattage << " MW\n\n";
}

std::string Blueprint::toString()
{
    return ". Bauplan";
}

void Blueprint::setKennzahl()
{
    int countWindPlant = 0;
    int countHydroPlant = 0;
    int countSolarPlant = 0;

    for (int i = 0; i < length; i++) {
        for (int j = 0; j < width; j++) {
            char type = buildArea[j][i].getLabel();
            if (type == 'H') { // HydroPlant
                countHydroPlant += 1;
            }
            else if (type == 'W') { // WindPlant
                countWindPlant += 1;
            }
            else if (type == 'S') { // SolarPlant
                countSolarPlant += 1;
            }
        }
        std::cout << "\n";
    }

    // Berechnung Kosten
    HydroPlant hydroPlant;
    WindPlant windPlant;
    SolarPlant solarPlant;

    double hydroMaterialCost = hydroPlant.getMaterialCost();
    double hydroPlantCost = hydroMaterialCost + hydroPlant.getNetCost();
    double hydroCost = hydroPlantCost * countHydroPlant;
    double hydroWattage = countHydroPlant * hydroPlant.getWattage();

    double windMaterialCost = windPlant.getMaterialCost();
    double windPlantCost = windMaterialCost + windPlant.getNetCost();
    double windCost = windPlantCost * countWindPlant;
    double windWattage = countWindPlant * windPlant.getWattage();

    double solarMaterialCost = solarPlant.getMaterialCost();
    double solarPlantCost = solarMaterialCost + solarPlant.getNetCost();
    double solarCost = solarPlantCost * countSolarPlant;
    double solarWattage = countSolarPlant * solarPlant.getWattage();

    double totalCost = hydroCost + windCost + solarCost;
    double totalWattage = hydroWattage + windWattage + solarWattage;
    int totalPowerplant = countHydroPlant + countWindPlant + countSolarPlant;

    // Berechnung Kennzahl
    kennZahl = (totalWattage) / totalCost * totalPowerplant;
}

double Blueprint::getKennzahl() {
    return kennZahl;
}

bool Blueprint::operator()(Building** a, Building** b)
{
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < width; j++) {
            if (a[j][i].getLabel() != b[j][i].getLabel()) {
                return false;
            }
        }
    }
    return true;
}
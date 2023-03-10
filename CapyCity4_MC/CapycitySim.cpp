#include "CapycitySim.h"
#include "Building.h"
#include "Material.h"
#include "Blueprint.h"
#include <iostream>
#include <vector>

std::vector<Blueprint> savedBlueprints;

// Aktueller plan, -1 weil noch kein Plan erstellt
// Variable dient dann als Index
int currentPlan = -1;

void CapycitySim::menu()
{
    std::string input;
    std::cout << "*********** MENU ***********" << std::endl;
    std::cout << "Gebaeude bauen (1)" << std::endl;
    std::cout << "Gebaeude abreissen (2)" << std::endl;
    std::cout << "Bauplan ausgeben (3)" << std::endl;
    std::cout << "Bauplaene verwalten (4)" << std::endl;
    std::cout << "Programm beenden (5)" << std::endl;
    std::cout << "Eingabe: ";
    std::cin >> input;
    std::cout << "****************************\n" << std::endl;

    if (regex_match(input, menuCheck)) {
        switch (stoi(input)) {

        case 1: // Geb?ude bauen
            if (savedBlueprints.size() == 0) {
                std::cout << "Du hast noch keine Bauplaene erstellt!\n\n\n";
                menu();
                break;
            }
            savedBlueprints.at(currentPlan).build();
            break;

        case 2: // Geb?ude abreissen
            if (savedBlueprints.size() == 0) {
                std::cout << "Du hast noch keine Bauplaene erstellt!\n\n\n";
                menu();
                break;
            }
            savedBlueprints.at(currentPlan).destroy();
            break;

        case 3: // Bauplan ausgeben
            if (savedBlueprints.size() == 0) {
                std::cout << "Du hast noch keine Bauplaene erstellt!\n\n\n";
                menu();
                break;
            }
            savedBlueprints.at(currentPlan).showBuildArea();
            break;

        case 4: // Baupl?ne verwalten
            planMenu();
            break;

        case 5: // Programm beenden
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

void CapycitySim::planMenu() {
    std::string input;
    std::cout << "*********** BLUEPRINT-MENU ***********" << std::endl;
    std::cout << "Bauplaene ausgeben (1)" << std::endl;
    std::cout << "Bauplan erstellen (2)" << std::endl;
    std::cout << "Zurueck zum Hauptmenue (3)" << std::endl;
    std::cout << "Eingabe: ";
    std::cin >> input;
    std::cout << "**************************************\n" << std::endl;

    switch (stoi(input)) {
    case 1:
        if (savedBlueprints.size() == 0) {
            std::cout << "Du hast noch keine Bauplaene erstellt!\n\n\n";
            menu();
            break;
        }
        else {
            showBlueprints();
        }
        break;

    case 2: // Bauplan erstellen
            // Iteration durch Blueprint-vektor
            for (int i = 0; i < savedBlueprints.size(); i++) {

                // Wenn aktueller Bauplan = index ist --> break (um Vergleich mit sich selbst zu vermeiden)
                if (i == currentPlan) {
                    break;
                }
                // Vergleich ob aktueller Bauplan identisch mit Bauplan am index vom Vektor ist
                if (Blueprint().operator()(savedBlueprints.at(currentPlan).buildArea, savedBlueprints.at(i).buildArea) == true) {
                    std::cout << "Dein aktueller Bauplan ist identisch mit einem vorherigen Bauplan\n";
                    std::cout << "Der Bauplan wird jetzt geloescht\n";
                    savedBlueprints.pop_back();
                    currentPlan -= 1;
                    break;
                } 
            }
        currentPlan += 1;
        savedBlueprints.push_back(Blueprint());
        std::cout << "Ein neuer Bauplan wurde erstellt\n";
        break;

    case 3: // Zur?ck zum Hauptmen?
        menu();
        break;
    default:
        std::cout << "Ungueltige Eingabe. Du wirst zur?ck ins Hauptmenue geschickt\n";
    }
}

void CapycitySim::showBlueprints() {
    // Sortieren der Baupl?ne nach Kennzahlen
    sort(savedBlueprints.begin(), savedBlueprints.end(), [](Blueprint a, Blueprint b) {
       return a.getKennzahl() > b.getKennzahl();
    });

    // Ausgabe der Baupl?ne in sortierter Reihenfolge mit Kennzahl
    for (int i = 0; i < savedBlueprints.size(); i++) {
        std::cout << i+1 << savedBlueprints[i].toString() << " | ";
        std::cout << "Kennzahl: " << savedBlueprints[i].getKennzahl() << "\n";
    }
}
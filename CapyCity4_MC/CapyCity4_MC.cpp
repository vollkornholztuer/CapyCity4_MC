// CapyCity_MC.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include "CapycitySim.h"
#include "Building.h"
#include "CapyCity4_MC.h"
#include "Blueprint.h"

using namespace std;
bool running = true;
std::regex menuCheck("[1-5]");
std::regex numberCheck("[[:digit:]]+");
int width = 0;
int length = 0;

int main(int argc, char** argv)
{
    if (argc != 3) {
        cout << "Verwendung: \n";
        cout << "CapyCity_MC <width> <height>\n";
        return 1;
    }

    try {
        width = stoi(argv[1]);
        length = stoi(argv[2]);
    }
    catch (invalid_argument const& ex) {
        ex;
        cout << "Eingabe besteht aus zwei ganzen Zahlen";
        return 2;
    }
    catch (out_of_range const& ex) {
        ex;
        cout << "Die Eingabe besteht NUR aus zwei ganzen Zahlen.";
        return 3;
    }

    CapycitySim menuCapy;

    while (running) {
        menuCapy.menu();
    }
}
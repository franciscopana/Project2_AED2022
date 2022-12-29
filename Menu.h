#ifndef TRABALHO2_MENU_H
#define TRABALHO2_MENU_H

#include <iostream>
#include <limits>
#include "Database.h"

using namespace std;

class Menu {
private:
    Database database;

public:
    Menu(Database& database) : database(database) {};

    void showInitialMenu();
    void showSearchFlightsMenu();
    void showSearchAirportsMenu();

    bool getYesOrNo();
    string getAirportCode();
    void clearScreen();
};


#endif //TRABALHO2_MENU_H

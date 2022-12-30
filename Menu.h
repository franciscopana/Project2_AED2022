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
    void listReachableAirports(string code);
    void listReachableCities(string code);
    void listReachableCountries(string code);
    void listDepartingAirlines(string code);

    bool getYesOrNo();
    string getAirportCode();
    int getNumberOfFlights();
};


#endif //TRABALHO2_MENU_H

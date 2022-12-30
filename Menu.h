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
    void listReachableAirports(string code, set<string>& airlines);
    void listReachableCities(string code, set<string>& airlines);
    void listReachableCountries(string code, set<string>& airlines);
    void listDepartingAirlines(string code);

    bool getYesOrNo();
    set<string> getAirlines();
    string getAirportCode();
    int getNumberOfFlights();
};


#endif //TRABALHO2_MENU_H

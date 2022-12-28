#ifndef TRABALHO2_MENU_H
#define TRABALHO2_MENU_H


#include "Database.h"

class Menu {
    public:
        void showInitialMenu(Database& database);
        void showSearchFlightsMenu(Database& database);
        void showSearchAirportsMenu(Database& database);

        bool getYesOrNo();
        string getAirportCode(Database& database);
        void clearScreen();
};


#endif //TRABALHO2_MENU_H

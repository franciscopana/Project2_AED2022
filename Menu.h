//
// Created by adria_ek1ciji on 28/12/2022.
//

#ifndef TRABALHO2_MENU_H
#define TRABALHO2_MENU_H


#include "Database.h"

class Menu {
    public:
        void showInitialMenu(Database& database);
        void showSearchFlightsMenu(Database& database);
        void showSearchAirportsMenu(Database& database);
};


#endif //TRABALHO2_MENU_H

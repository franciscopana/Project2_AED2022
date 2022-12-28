#include <iostream>

#include "App.h"
#include "Menu.h"

int main() {
    Database database;
    Menu menu;
    menu.showInitialMenu(database);
    return 0;
}

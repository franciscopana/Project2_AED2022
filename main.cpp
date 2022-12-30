#include <iostream>
#include "Menu.h"

int main() {
    Database database;
    Menu menu(database);
    menu.showInitialMenu();
    return 0;
}

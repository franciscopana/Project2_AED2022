#include <iostream>
#include "Menu.h"

int main() {
    Database database;
    Menu menu(database);
    //menu.showInitialMenu();
    string a = "LIS";
    string b = "JFK";
    database.printShortestPath(a,b);

    database.printPath(a, b);
    return 0;
}

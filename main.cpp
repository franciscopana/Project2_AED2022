#include <iostream>

#include "App.h"

int main() {
    Database database;
    string search = "OPO";
    database.printAirportsReachableFrom(search, 9);
    return 0;
}

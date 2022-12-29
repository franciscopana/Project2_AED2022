#include <iostream>

#include "App.h"

int main() {
    Database database;
    string search = "OPO";
    database.printCitiesReachableFrom(search, 2);
    return 0;
}

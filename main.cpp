#include <iostream>

#include "App.h"

int main() {
    Database database;
    string search = "OPO";
    database.printCountriesReachableFrom(search, 2);
    return 0;
}

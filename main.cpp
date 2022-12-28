#include <iostream>

#include "App.h"

int main() {
    Database database;
    string search = "London";
    database.printAirportsFromCity(search);
    return 0;
}

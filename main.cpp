#include <iostream>

#include "App.h"

int main() {
    Database database;
    string source = "OPO";
    string destination = "NAV";
    database.printPath(source, destination);
    return 0;
}

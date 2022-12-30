#include <iostream>

#include "App.h"

int main() {
    Database database;
    string source = "OPO";
    string destination = "LIS";
    database.printPath(source, destination);
    return 0;
}

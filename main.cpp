#include <iostream>

#include "App.h"

int main() {
    Database database;
    string source = "OPO";
    string destination = "SDU";
    database.printPath(source, destination);
    return 0;
}

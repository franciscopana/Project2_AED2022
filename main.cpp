#include <iostream>

#include "App.h"
#include "DatabaseViewer.h"

int main() {
    Database database;
    DatabaseViewer dbViewer(database);
    dbViewer.printFlights();
    return 0;
}

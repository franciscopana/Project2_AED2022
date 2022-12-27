#include <iostream>

#include "App.h"
#include "DatabaseViewer.h"

int main() {
    Database database;
    DatabaseViewer dbViewer(database);
    dbViewer.printFlightsFrom("OPO");
    return 0;
}

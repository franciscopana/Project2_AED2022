
#include <iostream>
#include "DatabaseViewer.h"

DatabaseViewer::DatabaseViewer(Database database) {
    this->database = database;
}

void DatabaseViewer::printAirlines() const {
    for(auto &airline : database.getAirlines()) {
        airline.second->print();
    }
}

void DatabaseViewer::printFlights() const {
    database.getFlights().printGraph();
}

void DatabaseViewer::printFlightsFrom(string airportCode) const {
    database.getFlights().printEdges(airportCode);
}
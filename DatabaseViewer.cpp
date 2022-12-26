
#include <iostream>
#include "DatabaseViewer.h"

DatabaseViewer::DatabaseViewer(Database database) {
    this->database = database;
}

void DatabaseViewer::printAirports() const {
    for(auto &airport : database.getAirports()) {
        airport.second->print();
    }
}

void DatabaseViewer::printAirlines() const {
    for(auto &airline : database.getAirlines()) {
        airline.second->print();
    }
}

void DatabaseViewer::printFlights() const {
    database.getFlights().printGraph();
}
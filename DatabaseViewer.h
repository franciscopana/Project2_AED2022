#ifndef TRABALHO2_DATABASEVIEWER_H
#define TRABALHO2_DATABASEVIEWER_H

#include "Database.h"

class DatabaseViewer{
private:
    Database database;

public:
    DatabaseViewer(Database database);
    void printAirlines() const;
    void printFlights() const;
    void printFlightsFrom(string airportCode) const;
};


#endif //TRABALHO2_DATABASEVIEWER_H

#ifndef TRABALHO2_DATABASEVIEWER_H
#define TRABALHO2_DATABASEVIEWER_H

#include "Database.h"

class DatabaseViewer{
private:
    Database database;

public:
    DatabaseViewer(Database database) ;
    void printAirports() const;
    void printAirlines() const;
    void printFlights() const;
};


#endif //TRABALHO2_DATABASEVIEWER_H

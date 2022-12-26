
#ifndef TRABALHO2_DATABASE_H
#define TRABALHO2_DATABASE_H


#include <map>
#include "Airport.h"
#include "Airline.h"
#include "Graph.h"

class Database {
private:
    map<string, Airport*> airports;
    map<string, Airline*> airlines;
    Graph flights;

    void loadAirports();
    void loadAirlines();
    void loadFlights();

public:
    Database();
    const map<string, Airport *> &getAirports() const;
    const map<string, Airline *> &getAirlines() const;
    const Graph &getFlights() const;

};

#endif //TRABALHO2_DATABASE_H

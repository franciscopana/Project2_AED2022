
#ifndef TRABALHO2_DATABASE_H
#define TRABALHO2_DATABASE_H


#include <map>
#include "Airport.h"
#include "Airline.h"
#include "Graph.h"

class Database {
private:
    /*
     * AIRPORTS
     * {string airport1Code : Airport* airport1, string airport2Code : Airport* airport2, ...}
     *
     * AIRLINES
     * {string airline1Code : Airline* airline1, string airline2Code : Airline* airline2, ...}
     * */
    map<string, Airport*> airports;
    map<string, Airline*> airlines;
    Graph flights;

    void loadAirports();
    void loadAirlines();
    void loadFlights();
public:
    Database();
};

#endif //TRABALHO2_DATABASE_H

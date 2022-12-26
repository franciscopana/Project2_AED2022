
#ifndef TRABALHO2_DATABASE_H
#define TRABALHO2_DATABASE_H


#include <map>
#include "Airport.h"
#include "Airline.h"
#include "Graph.h"

class Database {
    /*
     * AIRPORTS
     * {string airport1Code : Airport* airport1, string airport2Code : Airport* airport2, ...}
     *
     * AIRLINES
     * {string airline1Code : Airline* airline1, string airline2Code : Airline* airline2, ...}
     * */

private:
    map<string, Airline> airlines;
    map<string, Airport> airports;
    Graph flights;


    int loadAirports();
    void loadAirlines();
    void loadFlights();
    void printAirports();
    void printAirlines();
public:
    Database();
    const map<string, Airport> &getAirports() const;

};

#endif //TRABALHO2_DATABASE_H

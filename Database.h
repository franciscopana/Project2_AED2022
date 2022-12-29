
#ifndef TRABALHO2_DATABASE_H
#define TRABALHO2_DATABASE_H

#include "Airport.h"
#include "Airline.h"
#include "Graph.h"

class Database {
private:
    unordered_map<string, Airline*> airlines;
    unordered_map<string, set<Airport*>> cities;
    Graph flights;

    // Loaders
    void loadAirports();
    void loadAirlines();
    void loadFlights();

public:
    Database();

    // Printers
    void printAirlines() const;
    void printFlights() const;
    void printFlightsFrom(string& airportCode) const;
    void printAirportsFromCity(string& city) const;
    void printAirportsReachableFrom(string& airportCode, int flights);
    void printCitiesReachableFrom(string& airportCode, int nFlights);
    void printCountriesReachableFrom(string& airportCode, int nFlights);
};

#endif //TRABALHO2_DATABASE_H

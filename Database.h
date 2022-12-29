
#ifndef TRABALHO2_DATABASE_H
#define TRABALHO2_DATABASE_H

#include "Airport.h"
#include "Airline.h"
#include "Graph.h"

using namespace std;


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

    // Getters
    vector<set<string>> getCitiesReachableFrom(string& airportCode, int nFlights);
    vector<set<string>> getCountriesReachableFrom(string& airportCode, int nFlights);

    // Printers
    void printAirlines() const;
    void printAirportsFromCity(string& city) const;
    void printAirportsReachableFrom(string& airportCode, int flights);
    void printCitiesReachableFrom(string& airportCode, int nFlights);
    void printCountriesReachableFrom(string& airportCode, int nFlights);
};

#endif //TRABALHO2_DATABASE_H

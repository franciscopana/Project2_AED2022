
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

    void loadAirports();
    void loadAirlines();
    void loadFlights();

public:
    Database();

    bool hasAirport(const string& code) const;

    int getNumberOfFlights(string& airportCode) const;
    int getNumberOfAirlines(string& airportCode) const;
    void printFlightsFromAirport(string& airportCode) const;

    // Printers
    void printAirlines() const;
    void printFlights() const;
    void printAirlinesFromAirport(const string& airportCode) const;
    void printAirportsReachableFrom(string& airportCode, int flights);
    void printAirportsFromCity(string& city) const;
};

#endif //TRABALHO2_DATABASE_H

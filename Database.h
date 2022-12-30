
#ifndef TRABALHO2_DATABASE_H
#define TRABALHO2_DATABASE_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_set>
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

    // Booleans
    bool hasAirport(const string& code) const;

    // Getters
    vector<set<string>> getCitiesReachableFrom(string& airportCode, int nFlights);
    vector<set<string>> getCountriesReachableFrom(string& airportCode, int nFlights);
    set<string> getPath(string &source, string &destination);

    // Printers
    void printAirlines() const;
    void printAirlinesFromAirport(const string& airportCode) const;
    void printAirportsFromCity(string& city) const;
    void printAirportsReachableFrom(string& airportCode, int nFlights);
    void printCitiesReachableFrom(string& airportCode, int nFlights);
    void printCountriesReachableFrom(string& airportCode, int nFlights);
    void printPath(string &source, string &destination);

};

#endif //TRABALHO2_DATABASE_H

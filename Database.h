
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
    bool hasAirline(const string& code) const;

    // Getters
    vector<set<string>> getCitiesReachableFrom(string& airportCode, int nFlights, set<string>& airlines);
    vector<set<string>> getCountriesReachableFrom(string& airportCode, int nFlights, set<string>& airlines);
    set<string> getPath(string &source, string &destination);

    // Printers
    void printAirlinesFromAirport(string& airportCode);
    void printAirportsFromCity(string& city) const;
    void printAirportsReachableFrom(string& airportCode, int nFlights, set<string>& airlines);
    void printCitiesReachableFrom(string& airportCode, int nFlights, set<string>& airlines);
    void printCountriesReachableFrom(string& airportCode, int nFlights, set<string>& airlines);
    void printPath(string &source, string &destination, set<string>& airlines);
    void printShortestPath(string &source, string &destination, set<string>& airlines);

};

#endif //TRABALHO2_DATABASE_H

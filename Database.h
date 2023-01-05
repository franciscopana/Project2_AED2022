
#ifndef TRABALHO2_DATABASE_H
#define TRABALHO2_DATABASE_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_set>
#include <regex>
#include "Airport.h"
#include "Airline.h"
#include "Graph.h"
#include "City.h"

using namespace std;

class Database {
private:
    unordered_map<string, Airline*> airlines;
    unordered_map<string, set<Airport*>> citiesAirports;
    unordered_map<string, vector<City*>> citiesCoordinates;
    Graph flights;

    // Loaders
    void loadAirports();
    void loadAirlines();
    void loadFlights();
    void loadCities();

public:
    Database();

    // Booleans
    bool hasAirport(const string& code) const;
    bool hasAirline(const string& code) const;
    bool hasCity(const string& city) const;

    // Getters
    vector<string> getAirportsCodeFromCity(const string& city) const;
    vector<string> getAirportsCodeFromCoordinates(double latitude, double longitude, double radius);
    vector<set<string>> getCitiesReachableFrom(string& airportCode, int nFlights, set<string>& airlines);
    vector<set<string>> getCountriesReachableFrom(string& airportCode, int nFlights, set<string>& airlines);
    Airport* getAirport(const string& code) const;
    vector<string> getAirportsCodeFromCity(const string& city, double radius);
    vector<string> getAiportsCodeFromString(const string& codes) const;

    // Printers
    void printAirlinesFromAirport(string& airportCode);
    void printAirportsFromCity(string& city) const;
    void printAirportsReachableFrom(string& airportCode, int nFlights, set<string>& airlines);
    void printCitiesReachableFrom(string& airportCode, int nFlights, set<string>& airlines);
    void printCountriesReachableFrom(string& airportCode, int nFlights, set<string>& airlines);
    void printPaths(vector <string> &source, vector <string> &destination, set<string>& airlines);
    void printShortestPath(string &source, string &destination, set<string>& airlines);
    void printShortestPaths(vector<string>& source, vector<string>& destination, set<string>& airlines);
};

#endif //TRABALHO2_DATABASE_H

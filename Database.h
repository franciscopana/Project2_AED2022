
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
    unordered_map<string, Airline*> codeAirlines;
    unordered_map<string, Airline*> nameAirlines;

    unordered_map<string, set<Airport*>> countryAirports;
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

    // Getters
    vector<string> getAirportsCodeFromCountry(const string& input);
    vector<string> getAirportsCodeFromCoordinates(double latitude, double longitude, double radius);
    vector<set<string>> getCitiesReachableFrom(string& airportCode, int nFlights, set<string>& airlines);
    vector<set<string>> getCountriesReachableFrom(string& airportCode, int nFlights, set<string>& airlines);
    Airport* getAirport(const string& code) const;
    vector<string> getAirportsCodeFromCity(const string& city, double radius);
    vector<string> getAiportsCodeFromString(const string& codes) const;
    string getAirlineCode(const string& name) const;

    // Printers
    void printAirlinesFromAirport(string& airportCode);
    void printAirportsReachableFrom(string& airportCode, int nFlights, set<string>& airlines);
    void printCitiesReachableFrom(string& airportCode, int nFlights, set<string>& airlines);
    void printCountriesReachableFrom(string& airportCode, int nFlights, set<string>& airlines);
    void printRoute(pair<stack<Node*>, int>& p, set<string> &airlinesToFLy);
    void printPaths(vector <string> &source, vector <string> &destination, set<string>& airlines);
};

#endif //TRABALHO2_DATABASE_H

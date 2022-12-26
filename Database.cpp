
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "Database.h"

using namespace std;

int Database::loadAirports() {
    // reads dataset/airports.csv and creates a map of airports (its code and a reference to the airport object)
    // the map is stored in the airports attribute

    // the file has the following columns:
    // Code,Name,City,Country,Latitude,Longitude

    // TODO: implement this method

    ifstream file("../dataset/airports.csv");
    file.ignore(1000, '\n');
    if (!file.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }
    string line;
    while (std::getline(file, line)) {
        // Divide a linha em campos usando o caractere ',' como separador

        vector<string> fields;
        istringstream stream(line);
        string field;
        while (getline(stream, field, ',')) {
            fields.push_back(field);
        }
        if (fields.size() != 6) {
            std::cerr << "Invalid line on: " << line << std::endl;
            continue;
        }
        flights.addNode(fields[0], new Airport(fields[0], fields[1], fields[2], fields[3], stod(fields[4]), stod(fields[5])));
        Airport airport(fields[0], fields[1], fields[2], fields[3], stod(fields[4]), stod(fields[5]));
        airports.insert(pair<string, Airport >(fields[0], airport));
    }
}

void Database::printAirports() {
    // prints the airports map
    for(auto it = airports.begin(); it != airports.end(); ++it) {
        string name = it->second.getName();
        cout << it->first << " => " << name << endl;
    }
}



// TODO: implements loadAirlines() (similar to loadAirports())

void Database::loadAirlines(){
    ifstream file("../dataset/airlines.csv");
    file.ignore(1000, '\n');
    if (!file.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        return;
    }
    string line;
    while (std::getline(file, line)) {
        // Divide a linha em campos usando o caractere ',' como separador

        vector<string> fields;
        istringstream stream(line);
        string field;
        while (getline(stream, field, ',')) {
            fields.push_back(field);
        }
        if (fields.size() != 4) {
            std::cerr << "Invalid line on: " << line << std::endl;
            continue;
        }
        Airline airline = Airline(fields[0], fields[1], fields[2], fields[3]);
        airlines.insert(pair<string, Airline>(fields[0], airline));
    }
}

void Database::printAirlines() {
    // prints the airports map
    for(auto it = airlines.begin(); it != airlines.end(); ++it) {
        string name = it->second.getName();
        cout << it->first << " => " << name << endl;
    }
}



// TODO: implements loadFlights() (build our graph)
//Source,Target,Airline

void Database::loadFlights(){
    ifstream file("../dataset/flights.csv");
    file.ignore(1000, '\n');
    if (!file.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        return;
    }
    string line;
    while (std::getline(file, line)) {
        vector<string> fields;
        istringstream stream(line);
        string field;
        while (getline(stream, field, ',')) {
            fields.push_back(field);
        }
        if (fields.size() != 3) {
            std::cerr << "Invalid line on: " << line << std::endl;
            continue;
        }
        flights.addEdge(fields[0], fields[1], fields[2]);
    }
}

Database::Database() {
    loadAirports();
    //printAirports();
    loadAirlines();
    //printAirlines();
    loadFlights();
    flights.printGraph();
}

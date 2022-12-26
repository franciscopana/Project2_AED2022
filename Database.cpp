
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "Database.h"

using namespace std;

void Database::loadAirports() {
    ifstream file("../dataset/airports.csv");
    file.ignore(1000, '\n');
    if (!file.is_open()) {
        std::cerr << "Error opening file" << std::endl;
    }
    string line;
    while (std::getline(file, line)) {
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
        flights.addNode(fields[0], new Airport(fields[0], fields[1], fields[2], fields[3], stof(fields[4]), stof(fields[5])));
        auto* airport = new Airport(fields[0], fields[1], fields[2], fields[3], stof(fields[4]), stof(fields[5]));
        airports.insert(pair<string, Airport*> (fields[0], airport));
    }
    file.close();
}

void Database::loadAirlines(){
    ifstream file("../dataset/airlines.csv");
    file.ignore(1000, '\n');
    if (!file.is_open()) {
        cerr << "Error opening file" << std::endl;
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
        if (fields.size() != 4) {
            cerr << "Invalid line on: " << line << std::endl;
            continue;
        }
        auto* airline = new Airline(fields[0], fields[1], fields[2], fields[3]);
        airlines.insert(pair<string, Airline*>(fields[0], airline));
    }
    file.close();
}

void Database::loadFlights(){
    ifstream file("../dataset/flights.csv");
    file.ignore(1000, '\n');
    if (!file.is_open()) {
        cerr << "Error opening file" << std::endl;
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
            cerr << "Invalid line on: " << line << std::endl;
            continue;
        }
        flights.addEdge(fields[0], fields[1], fields[2]);
    }
}

Database::Database() {
    loadAirports();
    loadAirlines();
    loadFlights();
}

const map<string, Airport *> &Database::getAirports() const {
    return airports;
}

const map<string, Airline *> &Database::getAirlines() const {
    return airlines;
}

const Graph &Database::getFlights() const {
    return flights;
}

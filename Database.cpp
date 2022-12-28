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
        string code = fields[0];
        string city = fields[2];
        auto* airportPtr = new Airport(code, fields[1], city, fields[3], stof(fields[4]), stof(fields[5]));
        flights.addNode(code, airportPtr);

        auto cityIt = cities.find(city);
        if (cityIt != cities.end()) {
            cityIt->second.insert(airportPtr);
        } else {
            cities.insert({city, {airportPtr}});
        }
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

void Database::printAirlines() const {
    for(auto &airline : airlines) {
        airline.second->print();
    }
}

void Database::printFlights() const {
    flights.printGraph();
}

void Database::printFlightsFrom(string& airportCode) const {
    flights.printEdges(airportCode);
}

void Database::printAirportsReachableFrom(string &airportCode, int nFlights) {
    auto airports = flights.bfsWithNSteps(airportCode, nFlights);
    int flightsCounter = 0;
    unsigned totalFlights = 0;
    for (auto& airportsVector : airports) {
        if(airportsVector == airports.front()){
            cout << ">> Source Airport: "; airportsVector.front()->airport->printHeader(); cout << endl;
        } else {
            cout << ">> " << airportsVector.size() <<" Airports after " << flightsCounter << " flight(s):" << endl;
            totalFlights += airportsVector.size();
            for (auto& node : airportsVector) {
                cout << "     "; node->airport->printHeader(); cout << endl;
            }
        }
        flightsCounter++;
    }
    cout << ">> Total of " << totalFlights << " airports after " << nFlights << " flights." << endl;
}

void Database::printAirportsFromCity(string &city) const {
    auto cityIt = cities.find(city);
    if (cityIt != cities.end()) {
        cout << ">> "<< cityIt->second.size() << " airport(s) from " << city << ":" << endl;
        for (auto airport : cityIt->second) {
            cout << "     " << airport->getName() << " (" << airport->getCode() << ")\t|\tCoordinates: " << airport->getLatitude() << ", " << airport->getLongitude() << endl;
        }
    } else {
        cout << ">> No airports found in city " << city << endl;
    }
}

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_set>
#include "Database.h"

using namespace std;

/*    Loaders    */
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


/*    Printers    */
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

void Database::printAirportsReachableFrom(string &airportCode, int nFlights) {
    auto airports = flights.bfsWithNSteps(airportCode, nFlights);
    cout << ">> Source Airport: "; airports[0][0]->airport->printHeader(); cout << endl;
    unsigned totalFlights = 0;
    for (int i = 1; i < airports.size(); i++) {
        cout << ">> " << airports[i].size() << " Airports after " << i << " flight(s):" << endl;
        totalFlights += airports[i].size();
        for (auto& node : airports[i]) {
            cout << "     "; node->airport->printHeader(); cout << endl;
        }
    }
    cout << ">> Total of " << totalFlights << " airports reachable after " << nFlights << " flights." << endl;
}

void Database::printCitiesReachableFrom(string &airportCode, int nFlights) {

}

void Database::printCountriesReachableFrom(string &airportCode, int nFlights) {
    auto airports = flights.bfsWithNSteps(airportCode, nFlights);
    cout << ">> Source Airport: "; airports[0][0]->airport->printHeader(); cout << endl;

    unordered_set<string> countries;
    vector<set<string>> countriesByLevel;
    countriesByLevel.emplace_back();
    for(int i = 1; i < airports.size(); i++){
        for(auto& node : airports[i]){
            if(countries.insert(node->airport->getCountry()).second){
                if(countriesByLevel.size() < i+1){
                    countriesByLevel.push_back({node->airport->getCountry()});
                } else {
                    countriesByLevel[i].insert(node->airport->getCountry());
                }
            }
        }
    }

    for(int i = 1; i < countriesByLevel.size(); i++){
        cout << ">> " << countriesByLevel[i].size() << " Countries after " << i << " flight(s):" << endl;
        for(auto& country : countriesByLevel[i]){
            cout << "     " << country << endl;
        }
    }
    cout << ">> Total of " << countries.size() << " countries reachable after " << nFlights << " flights." << endl;
}

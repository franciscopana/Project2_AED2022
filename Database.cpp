#include <iomanip>
#include "Database.h"


/*    Loaders    */
void Database::loadAirports() {
    ifstream file("../dataset/airports.csv");
    file.ignore(1000, '\n');
    if (!file.is_open()) {
        cerr << "Error opening file" << std::endl;
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


/*   Booleans   */
bool Database::hasAirport(const std::string &code) const {
    return flights.hasAirport(code);
}

/*    Getters    */
vector<set<string>> Database::getCitiesReachableFrom(string &airportCode, int nFlights) {
    auto airports = flights.bfsWithNSteps(airportCode, nFlights);

    unordered_set<string> cities_;
    vector<set<string>> citiesByLevel;
    for(int i = 1; i < airports.size(); i++){
        for(auto& node : airports[i]){
            string city = node->airport->getCity() + ", " + node->airport->getCountry();
            if(cities_.insert(city).second){
                if(citiesByLevel.size() < i){
                    citiesByLevel.push_back({city});
                } else {
                    citiesByLevel[i-1].insert(city);
                }
            }
        }
    }
    return citiesByLevel;
}

vector<set<string>> Database::getCountriesReachableFrom(string &airportCode, int nFlights) {
    auto airports = flights.bfsWithNSteps(airportCode, nFlights);

    unordered_set<string> countries;
    vector<set<string>> countriesByLevel;
    for(int i = 1; i < airports.size(); i++){
        for(auto& node : airports[i]){
            string country = node->airport->getCountry();
            if(countries.insert(country).second){
                if(countriesByLevel.size() < i){
                    countriesByLevel.push_back({country});
                } else {
                    countriesByLevel[i-1].insert(country);
                }
            }
        }
    }
    return countriesByLevel;
}

set<string> Database::getPath(string &source, string &destination){

}

/*    Printers    */

void Database::printAirlinesFromAirport(std::string &airportCode) {
    auto airports = flights.bfsWithNSteps(airportCode, 1);
    set<string> airlines_;
    for(auto& node : airports[1]){
        for(auto& edge : node->edges){
            for(auto& airline : edge.airlines){
                airlines_.insert(airline);
            }
        }
    }

    cout << "There are a total of " << airlines_.size() << " airlines that fly from " << airportCode << endl;
    for(auto& airline : airlines_){
        cout << setw(5) << left << airline << setw(40) << left << airlines.at(airline)->getName() << setw(20) << left << airlines.at(airline)->getCountry() << endl;
    }
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
    cout << ">> Source Airport: "; airports[0][0]->airport->printHeader(); cout << endl;    unsigned totalFlights = 0;
    for (int i = 1; i < airports.size(); i++) {
        cout << ">> " << airports[i].size() << " airports after " << i << " flight(s):" << endl;
        totalFlights += airports[i].size();
        cout << " " << setw(20) << left << "Code" << setw(40) << left << "Name" << setw(20) << left << "Country" << endl;
        for (auto& node : airports[i]) {
            cout << " " << setw(20) << left << node->airport->getCode() << setw(40) << left << node->airport->getName() << setw(20) << left << node->airport->getCountry() << endl;
        }
    }
    cout << ">> Total of " << totalFlights << " airports reachable after " << nFlights << " flights." << endl;
}

void Database::printCitiesReachableFrom(string &airportCode, int nFlights) {
    auto citiesByLevel = getCitiesReachableFrom(airportCode, nFlights);
    unsigned totalCities = 0;
    cout << ">> Source Airport: "; flights.getNode(airportCode)->airport->printHeader() ; cout << endl;
    for(int i = 0; i < citiesByLevel.size(); i++){
        cout << ">> " << citiesByLevel[i].size() << " cities after " << i + 1 << " flight(s):" << endl;
        for(auto& city : citiesByLevel[i]){
            cout << "     " << city << endl;
        }
        totalCities += citiesByLevel[i].size();
    }
    cout << ">> Total of " << totalCities << " cities reachable after " << nFlights << " flights." << endl;
}

void Database::printCountriesReachableFrom(string &airportCode, int nFlights) {
    auto countriesByLevel = getCountriesReachableFrom(airportCode, nFlights);
    unsigned totalCountries = 0;
    cout << ">> Source Airport: "; flights.getNode(airportCode)->airport->printHeader() ; cout << endl;
    for(int i = 0; i < countriesByLevel.size(); i++){
        cout << ">> " << countriesByLevel[i].size() << " countries after " << i + 1 << " flight(s):" << endl;
        for(auto& country : countriesByLevel[i]){
            cout << "     " << country << endl;
        }
        totalCountries += countriesByLevel[i].size();
    }
    cout << ">> Total of " << totalCountries << " countries reachable after " << nFlights << " flights." << endl;
}

void Database::printPath(string &source, string &destination){
    auto paths = flights.bfsWithDest(source, destination);
    if(paths.empty()){
        cout << ">> No path found between " << source << " and " << destination << endl;
        return;
    }
    cout << ">> Path from " << source << " to " << destination << ":" << endl;
    for(auto& path : paths){
        cout << "     ";
        while(!path.empty()){
            cout << path.top()->airport->getName() << "  =>  ";
            path.pop();
        }
        cout << endl;
    }
}
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
        Airport* airportPtr = new Airport(code, fields[1], city, fields[3], stof(fields[4]), stof(fields[5]));
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

bool Database::hasAirline(const std::string &code) const {
    return airlines.find(code) != airlines.end();
}

/*    Getters    */
vector<set<string>> Database::getCitiesReachableFrom(string &airportCode, int nFlights, set<string> &airlines) {
    auto airports = flights.bfsWithNSteps(airportCode, nFlights, airlines);

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

vector<set<string>> Database::getCountriesReachableFrom(string &airportCode, int nFlights, set<string> &airlines) {
    auto airports = flights.bfsWithNSteps(airportCode, nFlights, airlines);

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

Airport* Database::getAirport(const std::string &code) const {
    return flights.getAirport(code);
}

void Database::printAirlinesFromAirport(string &airportCode) {
    list<Edge> edges = flights.getEdges(airportCode);
    set <string> airlines_ = {};
    for(auto& edge : edges){
        for(auto& airline : edge.airlines){
            if(airlines_.find(airline) == airlines_.end()){
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

void Database::printAirportsReachableFrom(string &airportCode, int nFlights, set<string> &airlines) {
    auto airports = flights.bfsWithNSteps(airportCode, nFlights, airlines);
    cout << ">> Source Airport: "; airports[0][0]->airport->printHeader(); cout << endl;    unsigned totalFlights = 0;

    for (int i = 1; i < airports.size(); i++) {
        cout << ">> " << airports[i].size() << " airports after " << i << " flight(s):" << endl;
        totalFlights += airports[i].size();
        cout << " " << setw(20) << left << "Code" << setw(40) << left << "Name" << setw(20) << left << "Country" << endl;
        for (auto& node : airports[i]) {
            cout << " " << setw(20) << left << node->airport->getCode() << setw(40) << left << node->airport->getName() << setw(20) << left << node->airport->getCountry() << endl;
        }
    }
    cout << ">> Total of " << totalFlights << " airports reachable after " << nFlights << " flight(s)." << endl;
}

void Database::printCitiesReachableFrom(string &airportCode, int nFlights, set<string> &airlines) {
    auto citiesByLevel = getCitiesReachableFrom(airportCode, nFlights, airlines);
    unsigned totalCities = 0;
    cout << ">> Source Airport: "; flights.getNode(airportCode)->airport->printHeader() ; cout << endl;
    for(int i = 0; i < citiesByLevel.size(); i++){
        cout << ">> " << citiesByLevel[i].size() << " cities after " << i + 1 << " flight(s):" << endl;
        for(auto& city : citiesByLevel[i]){
            cout << "     " << city << endl;
        }
        totalCities += citiesByLevel[i].size();
    }
    cout << ">> Total of " << totalCities << " cities reachable after " << nFlights << " flight(s)." << endl;
}

void Database::printCountriesReachableFrom(string &airportCode, int nFlights, set<string> &airlines) {
    auto countriesByLevel = getCountriesReachableFrom(airportCode, nFlights, airlines);
    unsigned totalCountries = 0;
    cout << ">> Source Airport: "; flights.getNode(airportCode)->airport->printHeader() ; cout << endl;
    for(int i = 0; i < countriesByLevel.size(); i++){
        cout << ">> " << countriesByLevel[i].size() << " countries after " << i + 1 << " flight(s):" << endl;
        for(auto& country : countriesByLevel[i]){
            cout << "     " << country << endl;
        }
        totalCountries += countriesByLevel[i].size();
    }
    cout << ">> Total of " << totalCountries << " countries reachable after " << nFlights << " flight(s)." << endl;
}

void Database::printPath(string &source, string &destination, set<string> &airlines) {
    auto paths = flights.bfsWithDest(source, destination, airlines);
    if (paths.empty()) {
        cout << ">> No path found between " << source << " and " << destination << endl;
        if(!airlines.empty()) {cout << ">> Using airlines: "; for(auto& airline : airlines) cout << airline << " "; cout << endl;}
        return;
    }
    cout << ">> " << paths.size() << " routes from " << source << " to " << destination << ":" << endl;

    unsigned nMinFlights = paths[0].size() - 1;

    for (auto &path: paths) {
        cout << "     ";
        while (path.size() > 1) {
            path.top()->airport->printHeader();
            cout << "\t=>\t";
            path.pop();
        }
        path.top()->airport->printHeader();
        cout << endl;
    }

    cout << ">> Minimum number of flights: " << nMinFlights << endl;
}

void Database::printShortestPath(string &source, string &destination, set<string> &airlines) {
    vector<Node*> path = flights.dijkstra(source, destination, airlines);
    if (path.empty()) {
        cout << ">> No path found between " << source << " and " << destination << endl;
        if(airlines.size() > 0){
            cout << ">> Using airlines: "; for(auto& airline : airlines) cout << airline << " "; cout << endl;
        }
        return;
    }
    cout << ">> Shortest route from " << source << " to " << destination << ":" << endl;
    cout << "     ";

    for(int i = 0; i < path.size() - 1; i++){
        path[i]->airport->printHeader();
        cout << "\t=>\t";
    }
    path.back()->airport->printHeader();
    cout << endl;
}

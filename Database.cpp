#include <iomanip>
#include "Database.h"

/*    Loaders    */
void Database::loadAirports() {
    ifstream file("../dataset/airports.csv");
    file.ignore(1000, '\n');
    if (!file.is_open()) {
        cerr << "Error opening file" << endl;
    }
    string line;
    while (getline(file, line)) {
        vector<string> fields;
        istringstream stream(line);
        string field;
        while (getline(stream, field, ',')) {
            fields.push_back(field);
        }
        if (fields.size() != 6) {
            cerr << "Invalid line on: " << line << endl;
            continue;
        }
        string code = fields[0];
        string city = fields[2];
        auto airportPtr = new Airport(code, fields[1], city, fields[3], stof(fields[4]), stof(fields[5]));
        flights.addNode(code, airportPtr);

        auto cityIt = citiesAirports.find(city);
        if (cityIt != citiesAirports.end()) {
            cityIt->second.insert(airportPtr);
        } else {
            citiesAirports.insert({city, {airportPtr}});
        }
    }
    file.close();
}

void Database::loadAirlines(){
    ifstream file("../dataset/airlines.csv");
    file.ignore(1000, '\n');
    if (!file.is_open()) {
        cerr << "Error opening file" << endl;
        return;
    }
    string line;
    while (getline(file, line)) {
        vector<string> fields;
        istringstream stream(line);
        string field;
        while (getline(stream, field, ',')) {
            fields.push_back(field);
        }
        if (fields.size() != 4) {
            cerr << "Invalid line on: " << line << endl;
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
        cerr << "Error opening file" << endl;
        return;
    }
    string line;
    while (getline(file, line)) {
        vector<string> fields;
        istringstream stream(line);
        string field;
        while (getline(stream, field, ',')) {
            fields.push_back(field);
        }
        if (fields.size() != 3) {
            cerr << "Invalid line on: " << line << endl;
            continue;
        }
        flights.addEdge(fields[0], fields[1], fields[2]);
    }
}

void Database::loadCities() {
    ifstream file("../dataset/worldcities.csv");
    file.ignore(1000, '\n');
    if (!file.is_open()) {
        cerr << "Error opening file" << endl;
        return;
    }
    string line;
    while (getline(file, line)) {
        if(line[line.size()-1] == '\r')
            line.resize(line.size()-1);
        vector<string> fields;
        istringstream stream(line);
        string field;
        while (getline(stream, field, ',')) {
            fields.push_back(field);
        }
        if (fields.size() != 4) {
            cerr << "Invalid line on: " << line << endl;
            continue;
        }

        string city = fields[0];
        string country = fields[3];
        double latitude = stod(fields[1]);
        double longitude = stod(fields[2]);

        auto cityPtr = new City(city, country, latitude, longitude);
        if(citiesCoordinates.find(city) != citiesCoordinates.end()){
            citiesCoordinates[city].push_back(cityPtr);
        } else {
            citiesCoordinates.insert({city, {cityPtr}});
        }
    }
    file.close();
}

Database::Database() {
    loadAirports();
    loadAirlines();
    loadFlights();
    loadCities();
}


/*   Booleans   */
bool Database::hasAirport(const string &code) const {
    return flights.hasAirport(code);
}

bool Database::hasAirline(const string &code) const {
    return airlines.find(code) != airlines.end();
}

bool Database::hasCity(const string &city) const {
    return citiesAirports.find(city) != citiesAirports.end();
}

/*    Getters    */
vector<string> Database::getAirportsCodeFromCity(const string& city) const {
    vector<string> airports;
    auto cityIt = citiesAirports.find(city);
    if (cityIt != citiesAirports.end()) {
        for (auto airport : cityIt->second) {
            airports.push_back(airport->getCode());
        }
    }
    return airports;
}

vector<string> Database::getAirportsCodeFromCoordinates(const double latitude,const double longitude, double radius) {
    vector<string> airports;

    for(auto node: flights.getNodes()){
        if(node->airport->getDistance(latitude, longitude) <= radius){
            airports.push_back(node->airport->getCode());
        }
    }
    return airports;
}

vector<set<string>> Database::getCitiesReachableFrom(string &airportCode, int nFlights, set<string> &airlinesToSearch) {
    auto airports = flights.bfsWithNSteps(airportCode, nFlights, airlinesToSearch);

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

vector<set<string>> Database::getCountriesReachableFrom(string &airportCode, int nFlights, set<string> &airlinesToSearch) {
    auto airports = flights.bfsWithNSteps(airportCode, nFlights, airlinesToSearch);

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

Airport* Database::getAirport(const string &code) const {
    return flights.getAirport(code);
}

vector<string> Database::getAirportsCodeFromCity(const string& city, double radius){
    auto cityIt = citiesCoordinates.find(city);
    if (cityIt == citiesCoordinates.end()) return {};

    auto cities = cityIt->second;
    City* c = cities[0];
    if(cities.size() > 1){
        cout << "Found " << cities.size() << " cities with the name " << city << endl;
        cout << "Please select one of the following cities:" << endl;
        for(int i = 0; i < cities.size(); i++){
            cout << i+1 << " - ";
            cities[i]->print();
        }
        int option;
        cout << ">> ";
        cin >> option;
        while(option < 1 || option > cities.size()){
            cout << "Invalid option. Please try again: ";
            cin >> option;
        }
        c = cities[option-1];
    }
    vector<string> airports = getAirportsCodeFromCoordinates(c->getLatitude(), c->getLongitude(), radius);
    return airports;
}

vector<string> Database::getAiportsCodeFromString(const std::string &codes) const {
    vector<string> airports;
    istringstream stream(codes);
    string code;
    while (getline(stream, code, ' ')) {
        if(!hasAirport(code)){
            return {};
        }
        airports.push_back(code);
    }
    return airports;
}


/*    Printers    */
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
    auto cityIt = citiesAirports.find(city);
    if (cityIt != citiesAirports.end()) {
        cout << ">> "<< cityIt->second.size() << " airport(s) from " << city << ":" << endl;
        for (auto airport : cityIt->second) {
            cout << "     " << airport->getName() << " (" << airport->getCode() << ")\t|\tCoordinates: " << airport->getLatitude() << ", " << airport->getLongitude() << endl;
        }
    } else {
        cout << ">> No airports found in city " << city << endl;
    }
}

void Database::printAirportsReachableFrom(string &airportCode, int nFlights, set<string> &airlinesToSearch) {
    auto airports = flights.bfsWithNSteps(airportCode, nFlights, airlinesToSearch);
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

void Database::printCitiesReachableFrom(string &airportCode, int nFlights, set<string> &airlinesToSearch) {
    auto citiesByLevel = getCitiesReachableFrom(airportCode, nFlights, airlinesToSearch);
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

void Database::printCountriesReachableFrom(string &airportCode, int nFlights, set<string> &airlinesToSearch) {
    auto countriesByLevel = getCountriesReachableFrom(airportCode, nFlights, airlinesToSearch);
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

void Database::printPaths(vector<string>& source, vector<string>& destination, set<string> &airlinesToSearch) {
    auto paths = flights.bfsWithDest(source, destination, airlinesToSearch);
    if (paths.empty()) {
        cout << ">> No path found between ";
        for(auto& s : source)
            cout << s << " ";
        cout << " and ";
        for(auto& d : destination)
            cout << d << " ";
        cout << endl;

        if(!airlinesToSearch.empty()){
            cout << ">> Using airlines: ";
            for(auto& airline : airlinesToSearch)
                cout << airline << " ";
            cout << endl;
        }
        return;
    }
    cout << ">> Total of " << paths.size() << " routes from ";
    for(auto& s : source)
        cout << s << " ";
    cout << " to ";
    for(auto& d : destination)
        cout << d << " ";
    cout << endl;

    unsigned numberToShow = paths.size();

    if(numberToShow > 3){
        cout << ">> How many routes do you want to see? ";
        cin >> numberToShow;
        while(numberToShow > paths.size() || numberToShow < 1){
            cout << ">> Invalid number. Please enter a number between 1 and " << paths.size() << ": ";
            cin >> numberToShow;
        }
    }


    for (int i = 0; i < numberToShow; i++) {
        auto p = paths[i];
        auto path = p.first;
        cout << "     ";
        while (path.size() > 1) {
            path.top()->airport->printHeader();
            cout << "\t=>\t";
            path.pop();
        }
        path.top()->airport->printHeader();
        cout << "\t|\t" << p.second << " km" << endl;
    }

    unsigned nMinFlights = paths[0].first.size() - 1;
    cout << ">> Minimum number of flights: " << nMinFlights << endl;
}

void Database::printShortestPath(string &source, string &destination, set<string> &airlinesToSearch) {
    vector<Node*> path = flights.dijkstra(source, destination, airlinesToSearch);
    if (path.empty()) {
        cout << ">> No path found between " << source << " and " << destination << endl;
        if(!airlinesToSearch.empty()){
            cout << ">> Using airlines: ";
            for(auto& airline : airlinesToSearch)
                cout << airline << " ";
            cout << endl;
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

void Database::printShortestPaths(vector<string>& source, vector<string>& destination, set<string>& airlinesToSearch){
    for(string sourceCode: source){
        for(string destCode: destination){
            printShortestPath(sourceCode, destCode, airlinesToSearch);
        }
    }
}

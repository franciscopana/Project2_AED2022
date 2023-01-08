#include <iomanip>
#include "Database.h"

/**
 * @brief Loads the data for airports in the file "airports.csv" into the database
 * @details For each line creates an Airport object and creates a node in the graph
 * Time complexity: O(N), where N is the number of lines in the airports.csv file
*/
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
        flights.addNode(code, airportPtr); //O(1)

        auto cityIt = citiesAirports.find(city); //O(1)
        if (cityIt != citiesAirports.end()) {
            cityIt->second.insert(airportPtr);
        } else {
            citiesAirports.insert({city, {airportPtr}});
        }
    }
    file.close();
}

/**
 * @brief Loads the data for flights in the file "flights.csv" into the database
 * @details For each line creates Airline object and adds it to unordered_map airlines
 * Time complexity: O(M), where M is the number of lines in the flights.csv file
*/
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
        codeAirlines.insert(pair<string, Airline*>(fields[0], airline));
        nameAirlines.insert(pair<string, Airline*>(fields[1], airline));
    }
    file.close();
}
/**
 * @brief Loads the data for flights in the file "flights.csv" into the database
 * @details For each line creates an edge in the graph where the source of the edge is the origin airport and the destination is the destination airport, the edge is labeled with the airline code
 * Time complexity: O(P), where P is the number of lines in the flights.csv file
*/
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

/**
 * @brief Loads the data for cities in the file "worldcities.csv" into the database
 * @details For each line creates a City object and adds it to the unordered_map citiesCoordinates
 * Time complexity: O(Q), where Q is the number of lines in the worldcities.csv file
*/
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

/**
 * @brief Constructor that initializes the Database by loading all data from the dataset files into memory
 * @details Time complexity: O(N+M+P+Q), where N is the number of lines in the airports.csv file, M is the number of lines in the airlines.csv file, P is the number of lines in the flights.csv file and Q is the number of lines in the worldcities.csv file
*/
Database::Database() {
    loadAirports();
    loadAirlines();
    loadFlights();
    loadCities();
}

/**
 * @brief Returns whether the airport with the given code is in the database
 * @details Time complexity: O(1)
*/
bool Database::hasAirport(const string &code) const {
    return flights.hasAirport(code);
}

/**
 * @brief Returns whether the airline with the given code is in the database
 * @details Time complexity: O(1)
*/
bool Database::hasAirline(const string &code) const {
    return codeAirlines.find(code) != codeAirlines.end() || nameAirlines.find(code) != nameAirlines.end();
}

/**
 * @brief Returns a vector of airport codes for all airports within a certain radius of the given coordinates
 * @details Time complexity: O(Q), where Q is the number of airports in the database
*/
vector<string> Database::getAirportsCodeFromCoordinates(const double latitude,const double longitude, double radius) {
    vector<string> airports;

    for(auto node: flights.getNodes()){
        if(node.second.airport->getDistance(latitude, longitude) <= radius){
            airports.push_back(node.second.airport->getCode());
        }
    }
    return airports;
}

/**
 * @brief Returns a vector of sets of cities that can be reached from the given airport within a certain number of flights and using only the given airlines
 * @details Time complexity: O(V+E), where V is the number of airports in the database and E is the number of flights in the database
*/
vector<set<string>> Database::getCitiesReachableFrom(string &airportCode, int nFlights, set<string> &airlinesToSearch) {
    auto airports = flights.bfsWithNSteps(airportCode, nFlights, airlinesToSearch); // O(V + E)

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

/**
 * @brief Returns a vector of sets of countries that can be reached from the given airport within a certain number of flights and using only the given airlines
 * @details Time complexity: O(V+E), where V is the number of airports in the database and E is the number of flights in the database
*/

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

/**
 * @brief Returns a pointer to the airport with the given code
 * @details Time complexity: O(1)
*/
Airport* Database::getAirport(const string &code) const {
    return flights.getAirport(code);
}

/**
 * @brief Returns a vector of airport codes for all airports within a certain radius of the given city
 * @details Time complexity: O(C) + O(Q), where C is the number of cities with the name city and Q is the number of airports in the database
*/
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
    if(airports.empty()){
        airports.emplace_back("not found");
    }
    return airports;
}

/**
 * @brief Returns a vector of airport codes for all airports with codes in the given string
 * @details Time complexity: O(M)
*/
vector<string> Database::getAiportsCodeFromString(const string &input) const {
    vector<string> airports;
    istringstream stream(input);
    string word;
    while (getline(stream, word, ' ')) {
        if(!hasAirport(word)){
            return {};
        }
        if(word.length()==3){airports.push_back(word);}
        else{
            airports.push_back(getAirlineCode(word));
        }

    }
    return airports;
}

/**
 * @brief Prints a list of all airlines that fly to the given airport
 * @details Time complexity: O(1)
*/
string Database::getAirlineCode(const std::string &name) const {
    auto it = nameAirlines.find(name);
    if(it != nameAirlines.end()){
        return it->second->getCode();
    }
    return "";
}

/**
 * @brief Prints the different airlines that fly from the given airport
 * @details Time complexity: O(E + A), where E is the number of edges in the adjacency list of the given airport and A is the number of airlines that fly from the given airport
*/
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
        cout << setw(5) << left << airline << setw(40) << left << codeAirlines.at(airline)->getName() << setw(20) << left << codeAirlines.at(airline)->getCountry() << endl;
    }
}

/**
 * @brief Prints a list of all airports that can be reached from the given airport within a certain number of flights and using only the given airlines
 * @details Time complexity: O(V + E), where V is the number of nodes in the graph(airports) and E is the number of edges in the graph(flights)
*/
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

/**
 * @brief Prints a list of cities that are reachable from the airport within the given number of flights, using only the specified airlines
 * @details Time complexity: O(V + E), where V is the number of nodes in the graph(airports) and E is the number of edges in the graph(flights)
*/
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

/**
 * @brief Prints a list of countries that are reachable from the airport within the given number of flights, using only the specified airlines.
 * @details Time complexity: O(V + E), where V is the number of nodes in the graph(airports) and E is the number of edges in the graph(flights)
*/
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

/**
 * @brief Given a pair of a stack of nodes and a distance, this method prints the route taken and the total distance of the route
 * @details Time complexity: O(N) where N is the number of nodes in the stack p
*/
void Database::printRoute(pair<stack<Node*>, int>& p, set<string> &airlinesToFLy){
    auto path = p.first;
    unsigned nFlights = p.first.size() - 1;
    bool first = true;
    cout << "   >> ";
    while (path.size() > 1) {
        if(!first) cout << "      ";
        Node* current = path.top();
        path.pop();
        Node* next = path.top();
        current->airport->printHeader();
        cout << "  ->  ";
        next->airport->printHeader();
        cout << "  |  ";
        set<string> allAirlines = current->getAirlinesTo(next->airport->getCode());
        if(!airlinesToFLy.empty()){
            set<string> intersection;
            set_intersection(allAirlines.begin(), allAirlines.end(), airlinesToFLy.begin(), airlinesToFLy.end(), inserter(intersection, intersection.begin()));
            allAirlines = intersection;
        }
        for(auto& airline : allAirlines){
            cout << airline << " ";
        }
        cout << endl;
        first = false;
    }
    cout << "      " << nFlights << " flight(s). Total distance: " << p.second << " km." << endl << endl;
}

/**
 * @brief Asks the user for the number of routes to be printed and prints the routes with the shortest distance
*/
unsigned askNumberToShow(unsigned max){
    if(max <= 3) return max;

    unsigned numberToShow;
    cout << ">> How many routes do you want to see? ";
    while (true){
        string line;
        getline(cin, line);
        stringstream ss(line);
        if (all_of(line.begin(), line.end(), ::isdigit) && ss >> numberToShow && numberToShow >= 1 && numberToShow <= max) {
            break;
        }
        if(!line.empty()){
            cout << ">> Invalid input. Please enter a number between 1 and " << max << ":  ";
        }
    }
    return (numberToShow > max) ? max : numberToShow;
}

/**
 * @brief This method takes in two vectors of strings representing the source and destination airports, and a set of airlines. It then prints all the paths from the source airports to the destination airports that can be taken by using any of the specified airlines.
 * @details Time complexity: O(V + E), where V is the number of nodes in the graph(airports) and E is the number of edges in the graph(flights)
*/
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

    cout << ">> Total of " << paths.size() << " route(s) from ";
    for(auto& s : source)
        cout << s << " ";
    cout << " to ";
    for(auto& d : destination)
        cout << d << " ";
    cout << endl;

    unsigned numberToShow = askNumberToShow(paths.size());

    for (int i = 0; i < numberToShow; i++) {
        printRoute(paths[i], airlinesToSearch);
    }
}

void Database::printFlightsFrom(string &airportCode) {
    flights.printEdges(airportCode);
}
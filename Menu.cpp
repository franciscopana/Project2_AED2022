#include <algorithm>
#include <iomanip>
#include <regex>
#include "Menu.h"


void Menu::showInitialMenu() {
    cout <<  "WELCOME TO THE FLIGHT SEARCH ENGINE" << endl;
    cout << "Please select an option:" << endl;
    cout << "1 - Search for flights" << endl;
    cout << "2 - Search for airports" << endl;
    cout << "3 - Exit" << endl;
    cout << ">> ";

    int option;
    cin >> option;
    if (cin.fail()) {
        cout << "Invalid input" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        showInitialMenu();
    }
    else {
        switch (option) {
            case 1:
                showSearchFlightsMenu();
                break;
            case 2:
                showSearchAirportsMenu();
                break;
            case 3:
                exit(0);
            default:
                cout << "Invalid option" << endl;
                showInitialMenu();
        }
    }
}

void Menu::showSearchFlightsMenu() {
    cout << "From: ";
    vector<string> origin = getAirportsCode();
    cout << "To: ";
    vector<string> destination = getAirportsCode();

    set<string> airlines = getAirlines();
    database.printPaths(origin, destination, airlines);

    cout << "Do you want to search for another flight? (y/n): ";
    if (getYesOrNo()) {
        showSearchFlightsMenu();
    }
    else {
        showInitialMenu();
    }
}

void Menu::showSearchAirportsMenu() {
    cout << "Please enter the airport code: ";
    string code = getAirportCode();

    Airport *airport = database.getAirport(code);
    cout  << airport->getName() << setw(20) << airport->getCity() << setw(20) << airport->getCountry() << endl << endl;

    cout << "Please select an option:" << endl;
    cout << "1 - How many different airports can be reached from " << code << "?\n";
    cout << "2 - How many different cities can be reached from " << code << "?\n";
    cout << "3 - How many different countries can be reached from " << code << "?\n";
    cout << "4 - How many different airlines depart from " << code << "?\n";
    cout << "5 - How many flights depart from " << code << "?\n";
    cout << ">> ";

    set<string> airlines = {};

    int option;
    cin >> option;
    if (cin.fail()) {
        cout << "Invalid input" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        showInitialMenu();
    }
    else {
        switch (option) {
            case 1:
                airlines = getAirlines();
                listReachableAirports(code, airlines);
                break;
            case 2:
                airlines = getAirlines();
                listReachableCities(code, airlines);
                break;
            case 3:
                airlines = getAirlines();
                listReachableCountries(code, airlines);
                break;
            case 4:
                listDepartingAirlines(code);
                break;
            default:
                cout << "Invalid option" << endl;
                showSearchAirportsMenu();
        }
    }
}

bool Menu::getYesOrNo(){
    string answer;
    cin >> answer;
    while (answer != "y" && answer != "Y" && answer != "n" && answer != "N") {
        cout << "Invalid input. Please enter y or n: ";
        cin >> answer;
    }
    return (answer == "y" || answer == "Y");
}

set<string> Menu::getAirlines() {
    set<string> airlines;
    cout << "Do you want to filter by airline? (y/n): ";
    if(getYesOrNo()){
        string airline;
        cout << "Please enter the airlines you want to use (enter 0 to exit): " << endl;
        cout << ">> ";
        cin >> airline;
        while (airline != "0") {
            if (database.hasAirline(airline)) {
                if(airline.size()==3) airlines.insert(airline);
                else airlines.insert(database.getAirlineCode(airline));
            }
            else {
                cout << "Airline not found. Try again: ";
            }
            cout << ">> ";
            cin >> airline;
        }
    }
    else airlines = {};

    return airlines;
}


int Menu::getNumberOfFlights(){
    cout << "How many flights are you willing to take? (1 for direct flights): ";
    int flights;
    cin >> flights;
    if (cin.fail()) {
        cout << "Invalid input" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        showInitialMenu();
    }
    else {
        if (flights >= 0) {
            return flights;
        }
        else {
            cout << "Invalid input" << endl;
            flights = getNumberOfFlights();
        }
    }
    return flights;
}

void Menu::listReachableAirports(string code, set<string>& airlines) {
    int nFlights = getNumberOfFlights();
    database.printAirportsReachableFrom(code, nFlights, airlines);

    int option;
    cout << "Please select an option:" << endl;
    cout << "1 - Change the number of flights" << endl;
    cout << "2 - Search for another airport" << endl;
    cout << "3 - Change the airlines" << endl;
    cout << "4 - Go back to the main menu" << endl;
    cout << ">> ";

    cin >> option;
    if (cin.fail()) {
        cout << "Invalid input" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        showInitialMenu();
    }
    else {
        switch (option) {
            case 1:
                listReachableAirports(code, airlines);
                break;
            case 2:
                showSearchAirportsMenu();
                break;
            case 3:
                airlines = getAirlines();
                listReachableAirports(code, airlines);
                break;
            case 4:
                showInitialMenu();
                break;
            default:
                cout << "Invalid option" << endl;
                listReachableAirports(code, airlines);
        }
    }
}


void Menu::listReachableCities(string code, set<string>& airlines) {
    int nFlights = getNumberOfFlights();
    database.printCitiesReachableFrom(code, nFlights, airlines);

    int option;
    cout << "Please select an option:" << endl;
    cout << "1 - Change the number of flights" << endl;
    cout << "2 - Search for another airport" << endl;
    cout << "3 - Go back to the main menu" << endl;
    cout << ">> ";

    cin >> option;
    if (cin.fail()) {
        cout << "Invalid input" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        showInitialMenu();
    }
    else {
        switch (option) {
            case 1:
                listReachableCities(code, airlines);
                break;
            case 2:
                showSearchAirportsMenu();
                break;
            case 3:
                showInitialMenu();
                break;
            default:
                cout << "Invalid option" << endl;
                listReachableCities(code, airlines);
        }
    }
}


void Menu::listReachableCountries(string code, set<string>& airlines) {
    int nFlights = getNumberOfFlights();
    database.printCountriesReachableFrom(code, nFlights, airlines);

    int option;
    cout << "Please select an option:" << endl;
    cout << "1 - Change the number of flights" << endl;
    cout << "2 - Search for another airport" << endl;
    cout << "3 - Go back to the main menu" << endl;
    cout << ">> ";

    cin >> option;
    if (cin.fail()) {
        cout << "Invalid input" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        showInitialMenu();
    }
    else {
        switch (option) {
            case 1:
                listReachableCountries(code, airlines);
                break;
            case 2:
                showSearchAirportsMenu();
                break;
            case 3:
                showInitialMenu();
                break;
            default:
                cout << "Invalid option" << endl;
                listReachableCountries(code, airlines);
        }
    }
}

void Menu::listDepartingAirlines(string code) {
    database.printAirlinesFromAirport(code);

    cout << "Please select an option:" << endl;
    cout << "1 - Search for another airport" << endl;
    cout << "2 - Go back to the main menu" << endl;
    cout << ">> ";

    int option;
    cin >> option;
    if (cin.fail()) {
        cout << "Invalid input" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        showInitialMenu();
    }
    else {
        switch (option) {
            case 1:
                showSearchAirportsMenu();
                break;
            case 2:
                showInitialMenu();
                break;
            default:
                cout << "Invalid option" << endl;
                listDepartingAirlines(code);
        }
    }
}

string Menu::getAirportCode() {
    string code;
    cin >> code;

    if (cin.fail()) {
        cout << "Invalid input" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        showInitialMenu();
    }
    else {
        if (code.length() != 3 || !all_of(code.begin(), code.end(), ::isalpha)) {
            cout << "Invalid airport code. Try again: ";
            code = getAirportCode();
        }
        else if (database.hasAirport(code)) {
            return code;
        }
        else {
            cout << "Airport not found. Try again: ";
            code = getAirportCode();
        }
    }
    return code;
}

vector<string> Menu::getAirportsCode() {
    while (true) {
        string input;
        getline(cin, input);

        vector<string> result;
        result = database.getAiportsCodeFromString(input);
        if(!result.empty()) return result;

        double radius = 100;
        result = database.getAirportsCodeFromCity(input, radius);
        if(!result.empty() && result[0] == "not found") {
            cout << "No airports found in a radius of " << radius << " km. Try again: ";
            continue;
        }
        if (!result.empty()) return result;

        regex coordinateRegex(R"(^(-?\d+(?:.\d+)?),(-?\d+(?:.\d+)?)$)");
        smatch coordinateMatch;
        if (regex_search(input, coordinateMatch, coordinateRegex)) {
            result = database.getAirportsCodeFromCoordinates(stod(coordinateMatch[1]), stod(coordinateMatch[2]), radius);
            if(!result.empty()) {
                return result;
            }
            cout << "No airports found in a "<< radius << " km radius of the coordinates " << coordinateMatch[1] << ", " << coordinateMatch[2] << endl;
        }

        if(!input.empty()) {
            cout << "It must either be the name of a city, a set of airports code or a pair of coordinates. Try again: ";
        }
    }
}
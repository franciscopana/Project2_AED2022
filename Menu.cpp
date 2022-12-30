#include "Menu.h"


void Menu::showInitialMenu() {
    cout << "Welcome to the Flight Search Engine!" << endl;
    cout << "Please select an option:" << endl;
    cout << "1 - Search for flights" << endl;
    cout << "2 - Search for airports" << endl;
    cout << "3 - Exit" << endl;

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
    cout << "Outbound Airport:" << endl;
    string origin = getAirportCode();
    cout << "Inbound Airport:" << endl;
    string destination = getAirportCode();
    database.printPath(origin, destination);

    cout << "Do you want to search for another flight? (y/n)" << endl;
    if (getYesOrNo()) {
        showSearchFlightsMenu();
    }
    else {
        showInitialMenu();
    }
}

void Menu::showSearchAirportsMenu() {
    cout << "Please enter the airport code:" << endl;
    string code = getAirportCode();

    cout << "Please select an option:" << endl;
    cout << "1 - How many different airports can be reached from " << code << "?\n";
    cout << "2 - How many different cities can be reached from " << code << "?\n";
    cout << "3 - How many different countries can be reached from " << code << "?\n";
    cout << "4 - How many different airlines depart from " << code << "?\n";
    cout << "5 - How many flights depart from" << code << "?\n";

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
                listReachableAirports(code);
            case 2:
                listReachableCities(code);
                break;
            case 3:
                listReachableCountries(code);
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
        if (database.hasAirport(code)) {
            return code;
        }
        else {
            cout << "Airport not found" << endl;
            code = getAirportCode();
        }
    }
    return code;
}

bool Menu::getYesOrNo(){
    string answer;
    cin>>answer;
    if(answer=="y" || answer=="Y"){
        return true;
    }
    if(answer=="n" || answer=="N"){
        return false;
    }
    cout<<"Invalid input. Please enter y or n."<<endl;
    answer = getYesOrNo();
}

int Menu::getNumberOfFlights(){
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

void Menu::listReachableAirports(string code){
    cout << "How many flights are you willing to take? (1 for direct flights)" << endl;
    int nFlights = getNumberOfFlights();
    database.printAirportsReachableFrom(code, nFlights);

    int option;
    cout << "Please select an option:" << endl;
    cout << "1 - Change the number of flights" << endl;
    cout << "2 - Search for another airport" << endl;
    cout << "3 - Go back to the main menu" << endl;

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
                listReachableAirports(code);
                break;
            case 2:
                showSearchAirportsMenu();
                break;
            case 3:
                showInitialMenu();
                break;
            default:
                cout << "Invalid option" << endl;
                listReachableAirports(code);
        }
    }
}

void Menu::listReachableCities(std::string code) {
    cout << "How many flights are you willing to take? (1 for direct flights)" << endl;
    int nFlights = getNumberOfFlights();
    database.printCitiesReachableFrom(code, nFlights);

    int option;
    cout << "Please select an option:" << endl;
    cout << "1 - Change the number of flights" << endl;
    cout << "2 - Search for another airport" << endl;
    cout << "3 - Go back to the main menu" << endl;

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
                listReachableCities(code);
                break;
            case 2:
                showSearchAirportsMenu();
                break;
            case 3:
                showInitialMenu();
                break;
            default:
                cout << "Invalid option" << endl;
                listReachableCities(code);
        }
    }
}

void Menu::listReachableCountries(std::string code) {
    cout << "How many flights are you willing to take? (1 for direct flights)" << endl;
    int nFlights = getNumberOfFlights();
    database.printCountriesReachableFrom(code, nFlights);

    int option;
    cout << "Please select an option:" << endl;
    cout << "1 - Change the number of flights" << endl;
    cout << "2 - Search for another airport" << endl;
    cout << "3 - Go back to the main menu" << endl;

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
                listReachableCountries(code);
                break;
            case 2:
                showSearchAirportsMenu();
                break;
            case 3:
                showInitialMenu();
                break;
            default:
                cout << "Invalid option" << endl;
                listReachableCountries(code);
        }
    }
}

void Menu::listDepartingAirlines(std::string code) {
    database.printAirlinesFromAirport(code);

    cout << "Please select an option:" << endl;
    cout << "1 - Search for another airport" << endl;
    cout << "2 - Go back to the main menu" << endl;

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
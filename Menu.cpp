//
// Created by adria_ek1ciji on 28/12/2022.
//

#include <iostream>
#include "Menu.h"
#include "Database.h"

using namespace std;

void Menu::showInitialMenu(Database& database) {
    cout << "Welcome to the Flight Search Engine!" << endl;
    cout << "Please select an option:" << endl;
    cout << "1 - Search for flights" << endl;
    cout << "2 - Search for airports" << endl;
    cout << "3 - Exit" << endl;

    int option;
    cin >> option;
    switch (option) {
        case 1:
            showSearchFlightsMenu(database);
            break;
        case 2:
            showSearchAirportsMenu(database);
            break;
        case 3:
            exit(0);
        default:
            cout << "Invalid option" << endl;
            showInitialMenu(database);
    }
}

void Menu::showSearchAirportsMenu(Database& database) {
    cout << "Please enter the airport code:" << endl;
    string code;
    cin >> code;

    cout << "Please select an option:" << endl;
    cout << "1 - How many flights depart from a given airport?" << endl;
    cout << "2 - How many different airlines depart from a given airport?" << endl;
    cout << "3 - How many different destinations can be reached from a given airport?" << endl;
    cout << "4 - How many different countries can be reached from a given airport?" << endl;

    int option;
    cin >> option;

    switch (option) {
        case 1:
            database.printFlightsFromAirport(code);
            break;
        case 2:
            //database.printAirlinesFromAirport(code);
            break;
        case 3:
            //database.printDestinationsFromAirport(code);
            break;
        case 4:
            //database.printCountriesFromAirport(code);
            break;
        default:
            cout << "Invalid option" << endl;
            showSearchAirportsMenu(database);
    }
}

void Menu::showSearchFlightsMenu(Database &database) {

}
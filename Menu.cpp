#include <iostream>
#include <limits>
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
    if (cin.fail()) {
        cout << "Invalid input" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        showInitialMenu(database);
    }
    else {
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
}

void Menu::showSearchFlightsMenu(Database &database) {

}

void Menu::showSearchAirportsMenu(Database& database) {
    string code = getAirportCode(database);

    cout << "Please select an option:" << endl;
    cout << "1 - How many flights depart from " << code << "?\n";
    cout << "2 - How many different airlines depart from " << code << "?\n";
    cout << "3 - How many different destinations can be reached from " << code << "?\n";
    cout << "4 - How many different countries can be reached from " << code << "?\n";

    int option;
    cin >> option;
    if (cin.fail()) {
        cout << "Invalid input" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        showInitialMenu(database);
    }
    else {
        switch (option) {
            case 1:
                cout<<"There are "<<database.getNumberOfFlights(code)<<" flights departing from "<<code<<". Do you want to see them? (y/n)"<<endl;
                if(getYesOrNo()){
                    database.printFlightsFromAirport(code);
                }
                break;
            case 2:
                cout<<"There are "<<database.getNumberOfAirlines(code)<<" airlines departing from "<<code<<". Do you want to see them? (y/n)"<<endl;
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

}

string Menu::getAirportCode(Database& database) {
    cout << "Please enter the airport code:" << endl;
    string code;
    cin >> code;

    if (cin.fail()) {
        cout << "Invalid input" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        showInitialMenu(database);
    }
    else {
        if (database.hasAirport(code)) {
            return code;
        }
        else {
            cout << "Airport not found" << endl;
            code = getAirportCode(database);
        }
    }
}

bool Menu::getYesOrNo(){
    string answer;
    cin>>answer;
    if(answer=="y" || answer=="Y"){
        return true;
    }
    else if(answer=="n" || answer=="N"){
        return false;
    }
    else{
        cout<<"Invalid input. Please enter y or n."<<endl;
        getYesOrNo();
    }
}


void Menu::clearScreen() {
    system("cls");
}
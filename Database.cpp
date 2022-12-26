
#include "Database.h"

void Database::loadAirports(){
    // reads dataset/airports.csv and creates a map of airports (its code and a reference to the airport object)
    // the map is stored in the airports attribute

    // the file has the following columns:
    // Code,Name,City,Country,Latitude,Longitude

    // TODO: implement this method
}

// TODO: implements loadAirlines() (similar to loadAirports())

void Database::loadAirlines(){

}

// TODO: implements loadFlights() (build our graph)

void Database::loadFlights(){

}

Database::Database() {
    loadAirports();
    loadAirlines();
    loadFlights();
}

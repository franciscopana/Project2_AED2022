#ifndef TRABALHO2_CITY_H
#define TRABALHO2_CITY_H

#include <iostream>
#include <string>

using namespace std;

class City {
private:
    string name;
    string country;
    double latitude;
    double longitude;

public:
    City(string& name, string& country, double latitude, double longitude) : name(name), country(country), latitude(latitude), longitude(longitude) {};
    double getLatitude() const { return latitude; }
    double getLongitude() const { return longitude; }
    void print() const;
    string getName() const { return name; }
};


#endif //TRABALHO2_CITY_H

#ifndef TRABALHO2_AIRPORT_H
#define TRABALHO2_AIRPORT_H

#include <iostream>
#include <string>

using namespace std;

/**
 * @class Airport
 * @brief Class that represents an airport
 */

class Airport {
private:
    string name;
    string code;
    string city;
    string country;
    double latitude;
    double longitude;

public:
    Airport(string& code, string& name, string& city , string& country, float latitude, float longitude);
    string getName();
    string getCode();
    string getCity();
    string getCountry();
    double getLatitude();
    double getLongitude();
    double getDistance(Airport* other);
    double getDistance(double latitude, double longitude);

    bool operator<(const Airport& other);

    void print() const;
    void printHeader() const;
};


#endif //TRABALHO2_AIRPORT_H

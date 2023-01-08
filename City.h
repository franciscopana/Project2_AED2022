#ifndef TRABALHO2_CITY_H
#define TRABALHO2_CITY_H

#include <iostream>
#include <string>

using namespace std;

/**
 * @class City
 * @brief Class that represents a city
*/
class City {
private:
    string name;
    string country;
    double latitude;
    double longitude;

public:

    City(string& name, string& country, double latitude, double longitude);

    double getLatitude() const;
    double getLongitude() const;
    string getName() const;
    void print() const;
};


#endif //TRABALHO2_CITY_H

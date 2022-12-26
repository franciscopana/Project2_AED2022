
#ifndef TRABALHO2_AIRPORT_H
#define TRABALHO2_AIRPORT_H

#include <string>

using namespace std;

class Airport {
private:
    string name;
    string code;
    string city;
    string country;
    float latitude;
    float longitude;

public:
    Airport(string& name, string& code, string& city, string& country, float latitude, float longitude);
    string getName();
    string getCode();
    string getCity();
    string getCountry();
    float getLatitude();
    float getLongitude();

    bool operator<(const Airport& other);
};


#endif //TRABALHO2_AIRPORT_H

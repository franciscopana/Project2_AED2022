
#include "Airport.h"

Airport::Airport(string& code, string& name, string& city, string& country, float latitude, float longitude) {
    this->name = name;
    this->code = code;
    this->city = city;
    this->country = country;
    this->latitude = latitude;
    this->longitude = longitude;
}

string Airport::getName() {
    return this->name;
}

string Airport::getCode() {
    return this->code;
}

string Airport::getCity() {
    return this->city;
}

string Airport::getCountry() {
    return this->country;
}

float Airport::getLatitude() {
    return this->latitude;
}

float Airport::getLongitude() {
    return this->longitude;
}

bool Airport::operator<(const Airport& other) {
    return this->code < other.code;
}

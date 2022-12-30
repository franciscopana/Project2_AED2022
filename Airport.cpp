#include "Airport.h"
#include <cmath>

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

float Airport::getDistance(Airport *other) {
    double dLat = (other->getLatitude() - this->latitude) * M_PI / 180.0;
    double dLon = (other->getLongitude() - this->longitude) * M_PI / 180.0;
    double lat1 = this->latitude * M_PI / 180.0;
    double lat2 = other->getLatitude() * M_PI / 180.0;

    double a = pow(sin(dLat / 2), 2) + pow(sin(dLon / 2), 2) * cos(lat1) * cos(lat2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    return 6371 * c;
}

bool Airport::operator<(const Airport& other) {
    return this->code < other.code;
}

void Airport::print() const {
    cout << "Code: " << code << "  |  Name: " << name << "  |  City: " << city << "  |  Country: " << country << "  |  Latitude: " << latitude << "  |  Longitude: " << longitude << endl;
}

void Airport::printHeader() const{
    cout << name << " (" << code << "), " << city  << ", " << country;
}

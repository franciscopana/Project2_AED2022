#include "Airport.h"
#include <cmath>

/**
 * @brief Class constructor that sets code, name, city, country, latitude and longitude
 * @details Time complexity: O(1)
*/
Airport::Airport(string& code, string& name, string& city, string& country, float latitude, float longitude) {
    this->name = name;
    this->code = code;
    this->city = city;
    this->country = country;
    this->latitude = latitude;
    this->longitude = longitude;
}
/**
 * @brief Returns the name of the airport
 * @details Time complexity: O(1)
 */
string Airport::getName() {
    return this->name;
}

/**
 * @brief Returns the code of the airport
 * @details Time complexity: O(1)
 */
string Airport::getCode() {
    return this->code;
}

/**
 * @brief Returns the city of the airport
 * @details Time complexity: O(1)
 */
string Airport::getCity() {
    return this->city;
}

/**
 * @brief Returns the country in which the airport is located
 * @details Time complexity: O(1)
 */
string Airport::getCountry() {
    return this->country;
}

/**
 * @brief Returns the latitude of the airport
 * @details Time complexity: O(1)
 */
double Airport::getLatitude() {
    return this->latitude;
}

/**
 * @brief Returns the longitude of the airport
 * @details Time complexity: O(1)
 */
double Airport::getLongitude() {
    return this->longitude;
}

/**
 * @brief Using the haversine formula returns the distance (in kilometers) between two airports.
 * @details Time complexity: O(1)
 */
double Airport::getDistance(Airport *other) {
    double dLat = (other->getLatitude() - this->latitude) * M_PI / 180.0;
    double dLon = (other->getLongitude() - this->longitude) * M_PI / 180.0;
    double lat1 = this->latitude * M_PI / 180.0;
    double lat2 = other->getLatitude() * M_PI / 180.0;

    double a = pow(sin(dLat / 2), 2) + pow(sin(dLon / 2), 2) * cos(lat1) * cos(lat2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    return 6371 * c;
}

/**
 * @brief Using the haversine formula returns the distance (in kilometers) between an airport and a given the latitude and longitude.
 * @details Time complexity: O(1)
 */
double Airport::getDistance(double latitude, double longitude) {
    double dLat = (latitude - this->latitude) * M_PI / 180.0;
    double dLon = (longitude - this->longitude) * M_PI / 180.0;
    double lat1 = this->latitude * M_PI / 180.0;
    double lat2 = latitude * M_PI / 180.0;

    double a = pow(sin(dLat / 2), 2) + pow(sin(dLon / 2), 2) * cos(lat1) * cos(lat2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    return 6371 * c;
}

/**
 * @brief Overloads the `<` operator for `Airport` objects.
 * @details Returns true if `this` airport's code is less than `other` airport's code, and false otherwise.
 * Time complexity: O(1)
 */
bool Airport::operator<(const Airport& other) {
    return this->code < other.code;
}

/**
 * @brief Prints a brief summary of the airport's information (name, code, city and country)
 * @details Time complexity: O(1)
 */
void Airport::printHeader() const{
    cout << name << " (" << code << "), " << city  << ", " << country;
}

#include "City.h"

/*
 * @brief Class constructor that sets name, country, latitude and longitude
 * @details Time complexity: O(1)
 * */
City::City(string& name, string& country, double latitude, double longitude){
    this->name = name;
    this->country = country;
    this->latitude = latitude;
    this->longitude = longitude;
}
/*
 * @brief Returns the latitude of the city
 * @details Time complexity: O(1)
 * */
double City::getLatitude() const {
    return latitude;
}

/*
 * @brief Returns the longitude of the city
 * @details Time complexity: O(1)
 * */
double City::getLongitude() const {
    return longitude;
}

/*
 * @brief Returns the name of the city
 * @details Time complexity: O(1)
 * */
string City::getName() const { return name; }

/*
 * @brief Prints the city's information (name, country, latitude and longitude)
 * @details Time complexity: O(1)
 * */
void City::print() const {
    cout << name << ", " << country << " (" << latitude << ", " << longitude << ")" << endl;
}
#include "Airline.h"

/*
 * @brief Class constructor that sets code, name, callSign and country
 * @details Time complexity: O(1)
*/
Airline::Airline(string& code, string& name, string& callSign, string& country){
    this->code = code;
    this->name = name;
    this->callSign = callSign;
    this->country = country;
};

/*
 * @brief Returns the code of the airline
 * @details Time complexity: O(1)
*/
string Airline::getCode() {
    return this->code;
}

/*
 * @brief Returns the name of the airline
 * @details Time complexity: O(1)
 * */
string Airline::getName() {
    return this->name;
}

/*
 * @brief Returns the callSign of the airline
 * @details Time complexity: O(1)
 * */
string Airline::getCallSign() {
    return this->callSign;
}

/*
 * @brief Returns the country of the airline
 * @details Time complexity: O(1)
 * */
string Airline::getCountry() {
    return this->country;
}

/*
 * @brief Overloads the `<` operator for `Airline` objects
 * @details Returns true if `this` airline's code is less than `other` airline's code, and false otherwise
 * Time complexity: O(1)
 * */
bool Airline::operator<(const Airline& other) {
    return this->code < other.code;
}

/*
 * @brief Prints the airline's information (code, name, callSign and country)
 * @details Time complexity: O(1)
 * */
void Airline::print() {
    cout << "Code: " << code << "  |  Name: " << name << "  |  Call Sign: " << callSign << "  |  Country: " << country << endl;
}
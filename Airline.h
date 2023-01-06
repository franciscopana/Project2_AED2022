#ifndef TRABALHO2_AIRLINE_H
#define TRABALHO2_AIRLINE_H

#include "iostream"
#include <string>

using namespace std;

/**
 * @class Airline
 * @brief Class that represents an airline
 */

class Airline {
private:
    string code;
    string name;
    string callSign;
    string country;

public:
    Airline(string& code, string& name, string& callSign, string& country);
    string getCode();
    string getName();
    string getCallSign();
    string getCountry();

    bool operator<(const Airline& other);

    void print();
};


#endif //TRABALHO2_AIRLINE_H

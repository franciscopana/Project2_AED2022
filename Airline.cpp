#include "Airline.h"

Airline::Airline(string& code, string& name, string& callSign, string& country){
    this->code = code;
    this->name = name;
    this->callSign = callSign;
    this->country = country;
};

string Airline::getCode() {
    return this->code;
}

string Airline::getName() {
    return this->name;
}

string Airline::getCountry() {
    return this->country;
}

bool Airline::operator<(const Airline& other) {
    return this->code < other.code;
}
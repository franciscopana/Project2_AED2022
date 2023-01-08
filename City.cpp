#include "City.h"

void City::print() const {
    cout << name << ", " << country << " (" << latitude << ", " << longitude << ")" << endl;
}
#include "side.h"
#include <iostream>

std::ostream& operator<<(std::ostream& os, const Side& side) {
    if (side == Side::Buy) {
        os << "Buy";
    } else {
        os << "Sell";
    }
    return os;
}
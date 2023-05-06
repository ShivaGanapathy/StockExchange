#pragma once

#include <ctime>
#include <string>
#include "side.h"

class Order {
public:
    std::string symbol;
    int volume;
    Side side;
    double price;
    std::time_t timestamp;
    Order();
};

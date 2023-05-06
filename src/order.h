#pragma once

#include <string>
#include <ctime>
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
#pragma once

#include <ctime>
#include "side.h"

template <typename symbol>
class Order {
    public:
        int volume;
        Side side;
        double price;
        std::time_t timestamp;
};
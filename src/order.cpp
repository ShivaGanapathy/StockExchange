#include <ctime>
#include <string>
#include <iostream>
#include "side.h"


class Order {
    public:
        std::string symbol;
        int volume;
        Side side;
        double price;
        std::time_t timestamp;
        Order () {std::cout << "order cons";}
};
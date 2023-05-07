#pragma once

#include <ctime>
#include <string>
#include "side.h"

class Order {
public:
    std::string m_symbol;
    int m_volume;
    Side m_side;
    double m_price;
    std::string m_timestamp;
    Order(std::string symbol, int volume, Side side, double price, std::string timestamp );
    bool operator==(const Order& other) const;
};

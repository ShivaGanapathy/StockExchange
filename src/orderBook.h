#pragma once

#include <vector>
#include <string>
#include "order.h"

class OrderBook {
    public:
        std::string m_symbol;
        std::vector<Order> m_orders;
        OrderBook();
        OrderBook(std::string symbol);
        OrderBook(const OrderBook& other);
};
#pragma once

#include <vector>
#include <string>
#include "order.h"

class OrderBook {
    int m_symbol;
    std::vector<Order> m_orders;
    public:
        OrderBook();
        OrderBook(int symbol);
};
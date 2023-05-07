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
        void addOrder(Order order);
        void cancelOrder(Order order);
        int numOrders();
        friend std::ostream& operator<<(std::ostream& os, const OrderBook& book);
};
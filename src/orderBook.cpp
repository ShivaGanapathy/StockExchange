#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "order.h"
#include "orderBook.h"


OrderBook::OrderBook() {
    // Default Constructor that is invoked during std_unordered map intialization
};

OrderBook::OrderBook(std::string symbol) {
    m_symbol = symbol;
    m_orders = std::vector<Order>();
};

OrderBook::OrderBook(const OrderBook& other) {
    m_symbol = other.m_symbol;
    m_orders = other.m_orders;
};

void OrderBook::addOrder(Order order) {
    m_orders.push_back(order);
};

void OrderBook::cancelOrder(Order order) {
    auto it = std::remove(m_orders.begin(), m_orders.end(), order);
    m_orders.erase(it, m_orders.end());
};

int OrderBook::numOrders() {
    return m_orders.size();
}

std::ostream& operator<<(std::ostream& os, const OrderBook& ob) {
    os << ob.m_symbol << " Orders:\n";
    for (const auto& order : ob.m_orders) {
        os << order;
    }
    os << "\n";
    return os;
}



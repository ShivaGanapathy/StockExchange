#include <iostream>
#include <vector>
#include <string>
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
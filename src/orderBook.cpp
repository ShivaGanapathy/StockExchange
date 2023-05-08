#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "order.h"
#include "orderBook.h"
#include "side.h"


OrderBook::OrderBook() {
    // Default Constructor that is invoked during std_unordered map intialization
};

OrderBook::OrderBook(std::string symbol) {
    m_symbol = symbol;
    m_current_id = 0;
    
};

OrderBook::OrderBook(const OrderBook& other) {
    m_symbol = other.m_symbol;
    m_buy_orders_vector = other.m_buy_orders_vector;
    m_sell_orders_vector = other.m_sell_orders_vector;
    m_buy_orders_pq = other.m_buy_orders_pq;
    m_sell_orders_pq = other.m_sell_orders_pq;
};

int OrderBook::addOrder(Order order, bool keep_id) {

    // When adding from client, this should execute. When adding from matching engine, this shouldn't
    if (!keep_id) {
        order.setId(m_current_id);
    }

    if (order.m_side == Side::Buy) {
        m_buy_orders_vector.push_back(order);
        m_buy_orders_pq.push(order);

    }
    else {
        m_sell_orders_vector.push_back(order);
        m_sell_orders_pq.push(order);
    }

    return m_current_id++;
    
};

void OrderBook::cancelOrder(Order order) {

    if (order.m_side == Side::Buy) {
        auto it = std::remove(m_buy_orders_vector.begin(), m_buy_orders_vector.end(), order);
        m_buy_orders_vector.erase(it, m_buy_orders_vector.end());
        
    }
    else {
        auto it = std::remove(m_sell_orders_vector.begin(), m_sell_orders_vector.end(), order);
        m_sell_orders_vector.erase(it, m_sell_orders_vector.end());
    }

    m_canceled_order_ids.insert(order.m_id);

    std::cout << "We cancelled the order with id " << std::to_string(order.m_id);

    
};

void OrderBook::removeOrder(Order order) {

    if (order.m_side == Side::Buy) {
        auto it = std::remove(m_buy_orders_vector.begin(), m_buy_orders_vector.end(), order);
        m_buy_orders_vector.erase(it, m_buy_orders_vector.end());
        
    }
    else {
        auto it = std::remove(m_sell_orders_vector.begin(), m_sell_orders_vector.end(), order);
        m_sell_orders_vector.erase(it, m_sell_orders_vector.end());
    }

    
};

int OrderBook::numOrders() {
    return m_buy_orders_vector.size() + m_sell_orders_vector.size();
}

std::ostream& operator<<(std::ostream& os, const OrderBook& ob) {
    os << ob.m_symbol << "Buy Orders:\n";
    for (const auto& order : ob.m_buy_orders_vector) {
        os << order;
    }
    os << "\n";
    os << ob.m_symbol << "Sell Orders:\n";
    for (const auto& order : ob.m_sell_orders_vector) {
        os << order;
    }
    os << "\n";
    return os;
}



#include <ctime>
#include <string>
#include <iostream>
#include "order.h"
#include "side.h"

Order::Order(std::string symbol, int volume, Side side, double price, std::time_t timestamp )
    : m_symbol(symbol), m_volume(volume), m_side(side), m_price(price), m_timestamp(timestamp)
{
    std::cout << "Order constructor called" << std::endl;
}

bool Order::operator==(const Order& other) const {
    return (m_symbol == other.m_symbol &&
            m_volume == other.m_volume &&
            m_side == other.m_side &&
            m_price == other.m_price &&
            m_timestamp == other.m_timestamp);
}

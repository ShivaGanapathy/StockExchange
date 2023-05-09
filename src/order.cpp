#include <ctime>
#include <string>
#include <iostream>
#include <boost/asio.hpp>
#include "order.h"
#include "side.h"

Order::Order(std::string symbol, int volume, Side side, double price, std::string timestamp, boost::reference_wrapper<boost::asio::ip::tcp::socket> socket )
    : m_symbol(symbol), m_volume(volume), m_side(side), m_price(price), m_timestamp(timestamp), m_id(-1), m_socket(socket) {}
    

bool Order::operator==(const Order& other) const {
    return (m_symbol == other.m_symbol &&
            m_volume == other.m_volume &&
            m_side == other.m_side &&
            m_price == other.m_price &&
            m_timestamp == other.m_timestamp);
}

void Order::setId(int id) {
    m_id = id;
}

std::ostream& operator<<(std::ostream& os, const Order& order) {
    os << "Symbol: " << order.m_symbol << ", Volume: " << order.m_volume << ", Side: " << order.m_side << ", Price: " << order.m_price << ", Timestamp: " << order.m_timestamp <<  " Id: " << order.m_id << std::endl;
    return os;
}

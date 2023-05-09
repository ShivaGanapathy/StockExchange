#pragma once

#include <ctime>
#include <string>
#include "side.h"
#include <boost/asio/ip/tcp.hpp>
#include <boost/ref.hpp>
#include <memory>

class Order {
public:
    std::string m_symbol;
    int m_volume;
    Side m_side;
    double m_price;
    std::string m_timestamp;
    int m_id;
    boost::reference_wrapper<boost::asio::ip::tcp::socket> m_socket;

    Order(std::string symbol, int volume, Side side, double price, std::string timestamp, boost::reference_wrapper<boost::asio::ip::tcp::socket> socket);
    void setId(int id);
    bool operator==(const Order& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Order& order);
};

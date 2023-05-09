#pragma once

#include <ctime>
#include <string>
#include "side.h"
#include "socketService.h"
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
    SocketService* m_socket_service;

    Order(std::string symbol, int volume, Side side, double price, std::string timestamp, SocketService* socket_service);
    Order& operator=(const Order& other) = default;
    void setId(int id);
    bool operator==(const Order& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Order& order);
};

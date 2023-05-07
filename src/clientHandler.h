#pragma once

#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <unordered_map>
#include "orderBook.h"

void handle_connection(boost::asio::ip::tcp::socket socket, std::unordered_map<std::string, OrderBook> orderBooks);
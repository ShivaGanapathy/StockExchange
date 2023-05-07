#pragma once

#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>

void handle_connection(boost::asio::ip::tcp::socket socket);
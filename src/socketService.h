#pragma once

#include <boost/asio.hpp>
#include <memory>
#include <mutex>
#include <boost/ref.hpp>

class SocketService {
    public:
        SocketService(boost::reference_wrapper<boost::asio::ip::tcp::socket> socket);
        ~SocketService();
        boost::reference_wrapper<boost::asio::ip::tcp::socket> m_socket;
        std::mutex* m_lock;
        void writeMessage(std::string msg);

};
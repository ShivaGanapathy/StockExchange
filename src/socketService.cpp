#include "socketService.h"
#include <boost/asio.hpp>
#include <boost/ref.hpp>
#include <iostream>

#include <mutex>

SocketService::SocketService(boost::reference_wrapper<boost::asio::ip::tcp::socket> socket): m_socket(socket) 
{
    // std::cout <<"yayuh\n" << std::endl;
    m_lock = new std::mutex();

}

SocketService::~SocketService() {
    std::cout << "Socket service was destructed\n";
}


void SocketService::writeMessage(std::string message) {
    // Aquire lock before reading to socket
    
    std::lock_guard<std::mutex> lock(*m_lock);
    boost::asio::write(m_socket.get(), boost::asio::buffer(message));
}
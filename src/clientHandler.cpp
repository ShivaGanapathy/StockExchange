#include "clientHandler.h"
#include <iostream>

void handle_connection(boost::asio::ip::tcp::socket  socket)
{
    try {
        while (true) {
            // Read data from the socket
            char data[1024];
            size_t length = socket.read_some(boost::asio::buffer(data));

            // Handle the received message
            std::string message(data, length);
            std::cout << "Received: " << message << std::endl;

            // Write a response back to the client
            std::string response = "Server received: ";
            boost::asio::write(socket, boost::asio::buffer(response));
        }
    }
    catch (std::exception& e) {
        std::cout << "Client connection closed\n";
    }
}
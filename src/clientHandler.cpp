#include "clientHandler.h"
#include "order.h"
#include "side.h"
#include <unordered_map>
#include <iostream>
#include <boost/ref.hpp>
#include <string>
#include <mutex>
#include <cstdio>
#include "socketService.h"

void handle_connection(boost::asio::ip::tcp::socket socket, std::unordered_map<std::string, OrderBook>& orderBooks)
{
    try {
        // Create a socket service that provides synchronization between multithreaded socket reads and writes
        SocketService socket_service(boost::ref(socket));

        while (true) {

            // Read data from the socket
            std::vector<char> data(20);
            size_t length = socket.read_some(boost::asio::buffer(data));
            std::string message(data.begin(), data.begin() + length);
            size_t start_pos = message.find("|9=");
            size_t end_pos = message.find("|", start_pos + 1);
            std::string str_num_bytes = message.substr(start_pos + 3, end_pos - start_pos - 3);
            int num_bytes = std::stoi(str_num_bytes);
            int num_remaining_bytes = num_bytes - length;

            std::vector<char> remaining(num_remaining_bytes);
            length = socket.read_some(boost::asio::buffer(remaining));
            std::string remaining_string(remaining.begin(), remaining.begin() + length);
            message += remaining_string;




            // For this specific FIX Message, create a mapping from code to value
            std::unordered_map<std::string, std::string> fix_mapping;

            // Handle the received message
            // std::string message(data, length);
            //std::cout << "Received: " << message << std::endl;
            std::vector<std::string> substrings;
            std::istringstream iss(message);
            std::string substring;

            // For each code to val mapping, insert into hashmap
            while (std::getline(iss, substring, '|')) {
                
                // Find the position of the first "=" character
                std::size_t pos = substring.find('=');
                // Extract the substring before the "=" character
                std::string code = substring.substr(0, pos);
                // Extract the substring after the "=" character
                std::string value = substring.substr(pos + 1);
                
                fix_mapping[code] = value;

            }

            // Support New Single Order's and else assume its a cancel order
            if (fix_mapping["35"] != "F") {
                // Create and add an order to the order book based off the client message
                std::string symbol = fix_mapping["55"];
                int volume = std::stoi(fix_mapping["38"]);
                Side side = fix_mapping["54"] == "1" ? Side::Buy : Side::Sell;
                double price = std::stod(fix_mapping["44"]);
                std::string timestamp = fix_mapping["52"];
                
                // Construct Order Object with extracted fields
                Order order(symbol, volume, side, price, timestamp, &socket_service);
                // Add Order To Order Book
                int confirmed_order_id = orderBooks[symbol].addOrder(order); 
                //std::cout << "hello?:" << (order.m_socket.get() == socket) << std::endl;
                // Send back order confirmation message
                
                std::string response;
                std::sprintf(&response[0], "8=FIX.4.2|9=170|35=8|37=%d|11=%s|55=%s|54=%s|38=%d|\n", confirmed_order_id, fix_mapping["11"].c_str(), symbol.c_str(), fix_mapping["54"].c_str(), volume );
                
                socket_service.writeMessage(response);
                //boost::asio::write(socket, boost::asio::buffer(response));

                
                
            }
            // Case to cancel an order
            else {
                std::string symbol = fix_mapping["55"];
                int volume = std::stoi(fix_mapping["38"]);
                Side side = fix_mapping["54"] == "1" ? Side::Buy : Side::Sell;
                double price = std::stod(fix_mapping["44"]);
                std::string timestamp = fix_mapping["52"];
                int order_id = std::stoi(fix_mapping["41"]);
                // Construct Order Object with extracted fields
                Order order(symbol, volume, side, price, timestamp, &socket_service);
                order.setId(order_id);
                // Cancel Order From Order Book
                orderBooks[symbol].cancelOrder(order);


            }

            

            // // Write a response back to the client
            // std::string response = "Server received: ";
            // boost::asio::write(socket, boost::asio::buffer(response));
        }
    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        std::cout << "Client connection closed" << std::endl;
    }
}
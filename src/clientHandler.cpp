#include "clientHandler.h"
#include "order.h"
#include "side.h"
#include <unordered_map>
#include <iostream>
#include <string>
#include <cstdio>


void handle_connection(boost::asio::ip::tcp::socket socket, std::unordered_map<std::string, OrderBook>& orderBooks)
{
    try {
        while (true) {
            // Read data from the socket
            char data[1024];
            size_t length = socket.read_some(boost::asio::buffer(data));


            // For this specific FIX Message, create a mapping from code to value
            std::unordered_map<std::string, std::string> fix_mapping;

            // Handle the received message
            std::string message(data, length);
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
                Order order(symbol, volume, side, price, timestamp);
                // Add Order To Order Book
                int confirmed_order_id = orderBooks[symbol].addOrder(order); 
                // Send back order confirmation message
                std::string response = "Server received: ";
                std::sprintf(&response[0], "8=FIX.4.2|9=170|35=8|37=%d|11=%s|55=%s|54=%s|38=%d|", confirmed_order_id, fix_mapping["11"].c_str(), symbol.c_str(), fix_mapping["54"].c_str(), volume );
                boost::asio::write(socket, boost::asio::buffer(response));

                
                
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
                Order order(symbol, volume, side, price, timestamp);
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
        std::cout << "Client connection closed\n";
    }
}
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <sstream>
#include <ctime>
#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <thread>
#include "orderBook.h"
#include "order.h"
#include "side.h"

using namespace boost::asio;
using ip::tcp;


void handle_connection(tcp::socket socket)
{
    try
    {
        std::cout << "Connected" << std::endl;

        // Read data from the client
        boost::asio::streambuf buf;
        boost::asio::read_until(socket, buf, "\n");
        std::string data = boost::asio::buffer_cast<const char*>(buf.data());
        std::cout << "Received: " << data << std::endl;

        // Write response back to the client
        std::string response = "Server received: " + data;
        boost::asio::write(socket, boost::asio::buffer(response));
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}


int main() {
    std::cout << "Hello world" << std::endl;
    // Read all ticker symbols and create and create a mapping of symbol to orderbook for each one
    std::ifstream t("../data/symbols.txt");
    std::stringstream buffer;
    buffer << t.rdbuf();
    t.close();

    // Create an unordered map with a symbol as the key and an OrderBook for each symbol as the value
    std::unordered_map<std::string, OrderBook> orderBooks;

    
    // Populate map by creating OrderBooks for each symbol
    std::string symbol;
    while (std::getline(buffer, symbol, '\n')) {
        OrderBook book(symbol);
        orderBooks[symbol] = book;
        
    }

    // Try creating a new Order
    Order order("AAPL", 10, Side::Buy, 50.14, std::time(nullptr) );

    // Try adding an order into an orderBook
    orderBooks["AAPL"].addOrder(order);

    // Try removing and order from the orderBook
    orderBooks["AAPL"].cancelOrder(order);

    // Begin TCP server
    // Create an IO context
    boost::asio::io_context io_context;

    // Create a TCP acceptor to listen for connections on port 8080
    tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 8080));

    // Run the IO context in a separate thread
    std::thread th([&io_context]() { io_context.run(); });

    while (true) {
        // Wait for a client to connect
        tcp::socket socket(io_context);
        acceptor.accept(socket);

        // Handle the connection in a separate thread
        std::thread(handle_connection, std::move(socket)).detach();
    }

    // Join the thread
    th.join();


    

    
}
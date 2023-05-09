#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <sstream>
#include <ctime>
#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <thread>
#include <boost/ref.hpp>
#include "orderBook.h"
#include "order.h"
#include "side.h"
#include "clientHandler.h"
#include "matchingEngine.h"

using namespace boost::asio;
using ip::tcp;


int main() {
    // Read all ticker symbols and create and create a mapping of symbol to orderbook for each one
    std::ifstream t("../data/symbols.txt");
    std::stringstream buffer;
    buffer << t.rdbuf();
    t.close();

    // Create an unordered map with a symbol as the key and an OrderBook for each symbol as the value
    std::unordered_map<std::string, OrderBook> orderBooks;

    
    // Populate map by creating OrderBooks for each symbol
    std::string symbol;
    std::vector<std::thread> threads;
    while (std::getline(buffer, symbol, '\n')) {
        OrderBook book(symbol);
        orderBooks[symbol] = book;
        // For each symbol, spin up a matching engine thread
        auto x = std::ref(orderBooks[symbol]);
        threads.emplace_back(std::thread(matching_engine, x ));
    }

    // Create a throwaway socket to create a dummy order
    boost::asio::io_service throwaway_io_service;
    boost::asio::ip::tcp::socket throwaway_socket(throwaway_io_service);


    // Try creating a new Order
    Order order("AAPL", 10, Side::Buy, 50.14, "NOW", boost::ref(throwaway_socket) );

    // Try adding an order into an orderBook
    orderBooks["AAPL"].addOrder(order);

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
        std::thread(handle_connection, std::move(socket), std::ref(orderBooks)).detach();
    }

    // Join the thread
    th.join();


    // Join the threads
    for (auto& t : threads) {
        t.join();
    }


    
}
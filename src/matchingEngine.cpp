#include "matchingEngine.h"
#include <iostream>
#include <boost/asio.hpp>


void matching_engine(OrderBook& orderBook) {
    // IF the orderbook is apple, let's print out the state of the order book every 5 seconds
    if (orderBook.m_symbol == "AAPL") {
        while (true) {
            std::cout << orderBook << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(4));
        }
    }
    
}
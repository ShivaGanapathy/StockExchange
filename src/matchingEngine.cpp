#include "matchingEngine.h"
#include <iostream>
#include <algorithm>
#include <queue>
#include <boost/asio.hpp>


void matching_engine(OrderBook& orderBook) {
    
    //IF the orderbook is apple, let's print out the state of the order book every 5 seconds
    // if (orderBook.m_symbol == "AAPL") {
    //     while (true) {
    //         std::cout << orderBook << std::endl;
    //         std::this_thread::sleep_for(std::chrono::seconds(4));
    //     }
    // }
    // else {
    //     return;
    // }


    while (true) {

        // While we have a bidder willing to buy at or above the lowest ask price
        while (orderBook.m_buy_orders_pq.size() > 0 && orderBook.m_sell_orders_pq.size() > 0 && orderBook.m_buy_orders_pq.top().m_price >= orderBook.m_sell_orders_pq.top().m_price) {
            
            Order bid = orderBook.m_buy_orders_pq.top();
            Order ask = orderBook.m_sell_orders_pq.top();
            orderBook.m_buy_orders_pq.pop();
            orderBook.m_sell_orders_pq.pop();
            orderBook.removeOrder(bid);
            orderBook.removeOrder(ask);
            // Determine at what volume we can match each request.
            int matching_volume = std::min(bid.m_volume, ask.m_volume);

            // Create a match object to send to both the bidder and seller
            std::cout << "Match! betweeen: " << bid << "\n" << ask << std::endl;
    
            std::string response = "Your buy order of id " + std::to_string(bid.m_id) +   " was matched!\n";
            boost::asio::write(bid.m_socket.get(), boost::asio::buffer(response));
            
            response =  "Your sell order of id " + std::to_string(ask.m_id) +   " was matched!\n";
            boost::asio::write(ask.m_socket.get(), boost::asio::buffer(response));


            // If any order only partially filled, reinsert order into the pq after subtracting the matching volume
            bid.m_volume -= matching_volume;
            ask.m_volume -= matching_volume;

            if (bid.m_volume > 0) {
                orderBook.m_buy_orders_pq.push(bid);
                orderBook.addOrder(bid, true);
            }
            

            if (ask.m_volume > 0) {
                orderBook.m_sell_orders_pq.push(ask);
                orderBook.addOrder(ask, true);
            }
            
        }
        
        // Instead of polling, let's wait for more orders to accumulate in the books before trying to match.
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    
    
}
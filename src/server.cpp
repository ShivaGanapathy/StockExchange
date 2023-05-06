#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <sstream>
#include <ctime>
#include "orderBook.h"
#include "order.h"
#include "side.h"


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



    

    
}
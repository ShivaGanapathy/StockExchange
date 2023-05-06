#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <sstream>
#include "orderBook.h"
#include "order.h"


int main() {
    std::cout << "Hello world" << std::endl;
    // Read all ticker symbols and create and create a mapping of symbol to orderbook for each one
    std::ifstream t("../data/symbols.txt");
    std::stringstream buffer;
    buffer << t.rdbuf();
    t.close();

    // create an unordered map with a symbol as the key and an OrderBook for each symbol as the value
    std::unordered_map<std::string, int> orderBooks;
    std::string symbol;

    
    Order order;
    
    // std::string line;
    // while (std::getline(buffer, line, '\n')) {
    //     orderBooks[line.str] = OrderBook(line);
    // }

    //test the unordered map by printing the symbols and their associated OrderBooks
    // for (const auto& [symbol, orderBook] : orderBooks) {
    //     std::cout << symbol << ": " << orderBook.m_symbol << std::endl;
    // }
}
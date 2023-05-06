#include <iostream>
#include <vector>
#include <string>
#include "order.h"


class OrderBook {
    int m_symbol;
    std::vector<Order> m_orders;
    public:
        OrderBook(){std::cout << "def cons";}
        OrderBook(int symbol) {
            m_symbol = symbol;
        }
};
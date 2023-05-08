#pragma once

#include <vector>
#include <string>
#include <queue>
#include <unordered_set>
#include "order.h"
#include "priceComparators.h"

class OrderBook {
    public:
        std::string m_symbol;
        std::vector<Order> m_buy_orders_vector;
        std::vector<Order> m_sell_orders_vector;
        std::priority_queue<Order, std::vector<Order>, LowPriceComparator> m_sell_orders_pq;
        std::priority_queue<Order, std::vector<Order>, HighPriceComparator> m_buy_orders_pq;
        std::unordered_set<int> m_canceled_order_ids; 
        int m_current_id;

        OrderBook();
        OrderBook(std::string symbol);
        OrderBook(const OrderBook& other);
        int addOrder(Order order);
        void cancelOrder(Order order);
        int numOrders();
        friend std::ostream& operator<<(std::ostream& os, const OrderBook& book);
};
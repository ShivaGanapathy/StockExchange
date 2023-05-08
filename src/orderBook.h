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
        std::priority_queue<Order, std::vector<Order>, HighPriceComparator> m_sell_orders_pq;
        std::priority_queue<Order, std::vector<Order>, LowPriceComparator> m_buy_orders_pq;
        std::unordered_set<int> m_canceled_order_ids; 
        int m_current_id;

        OrderBook();
        OrderBook(std::string symbol);
        OrderBook(const OrderBook& other);
        int addOrder(Order order, bool keep_id=false);
        // Initated by client, removes from pq as well as vector
        void cancelOrder(Order order);
        // Initated by matching engine, removes from only vector
        void removeOrder(Order order);
        int numOrders();
        friend std::ostream& operator<<(std::ostream& os, const OrderBook& book);
};
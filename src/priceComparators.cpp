#include <queue>
#include "order.h"
#include "priceComparators.h"

// Custom comparator for lowest price then most recent order
bool LowPriceComparator::operator()(const Order& lhs, const Order& rhs) const {
    if (lhs.m_price < rhs.m_price) {
        return true;
    } else if (lhs.m_price == rhs.m_price) {
        return lhs.m_timestamp > rhs.m_timestamp;
    }
    return false;
}

bool HighPriceComparator::operator()(const Order& lhs, const Order& rhs) const {
    if (lhs.m_price > rhs.m_price) {
        return true;
    } else if (lhs.m_price == rhs.m_price) {
        return lhs.m_timestamp > rhs.m_timestamp;
    }
    return false;
}
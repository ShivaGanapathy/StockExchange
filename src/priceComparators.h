#pragma once

#include <queue>
#include "order.h"

// Custom comparator for lowest price then most recent order
struct LowPriceComparator {
    bool operator()(const Order& lhs, const Order& rhs) const;
};

// Custom comparator for highest price then most recent order
struct HighPriceComparator {
    bool operator()(const Order& lhs, const Order& rhs) const;
};
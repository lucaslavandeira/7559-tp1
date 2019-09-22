#include <algorithm>
#include "Order.h"

Order::Order(unsigned int roses, unsigned int tulips) : roses(roses), tulips(tulips) {
}

Order::Order(const Order& other) noexcept :
    roses(other.roses),
    tulips(other.tulips) {
}

bool Order::isFulfilled() {
    return fulfilled;
}

void Order::markFulfilled() {
    fulfilled = true;
}

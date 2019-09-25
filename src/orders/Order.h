#ifndef TP1_ORDER_H
#define TP1_ORDER_H


class Order {
public:
    unsigned int roses;
    unsigned int tulips;

protected:
    bool fulfilled = false;
public:
    Order(const Order& other) noexcept;
    Order(unsigned int roses, unsigned int tulips);
    /*
    Check if order is already completed
    */
    bool isFulfilled();
    /*
    Marks an order as completed
    */
    void markFulfilled();
};


#endif //TP1_ORDER_H

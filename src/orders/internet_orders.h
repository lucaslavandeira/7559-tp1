#ifndef TP1_INTERNET_ORDERS_H
#define TP1_INTERNET_ORDERS_H


#include <string>
#include <fstream>
#include "Order.h"

class InternetOrders {
    const int chain_id;
    const std::string orders_dir;
    unsigned int row;
    Order current_order;
    std::ifstream file;
    bool out_of_orders = false;
public:
    InternetOrders(int chain_id, const std::string orders_dir);

    Order & get_current_order();
    bool orders_remaining();
    ~InternetOrders();

private:
    void parse_line();
    std::string get_order_dir();
};


#endif //TP1_INTERNET_ORDERS_H

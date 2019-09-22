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
public:
    InternetOrders(int chain_id, const std::string orders_dir);

    Order & get_current_order();
    ~InternetOrders();

private:
    void parse_line();
    std::string get_order_dir();
};


#endif //TP1_INTERNET_ORDERS_H

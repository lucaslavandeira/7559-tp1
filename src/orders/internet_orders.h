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
    /*
    Gets the current order
    */
    Order & get_current_order();
    /*
    Check if there are orders remaining to process
    */
    bool orders_remaining();
    ~InternetOrders();

private:
    /*
    Parses lines from the Order file
    */
    void parse_line();
    /*
    Returns the directory of the orders
    */
    std::string get_order_dir();
};


#endif //TP1_INTERNET_ORDERS_H

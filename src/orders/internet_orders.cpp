#include <sstream>
#include <iostream>
#include "internet_orders.h"
#include "NullOrder.h"
#include "../util/get_number_from_file.h"

InternetOrders::InternetOrders(int chain_id, const std::string &orders_dir) :
        chain_id(chain_id),
        orders_dir(orders_dir),
        row(0),
        current_order(NullOrder()) {
    const std::string& dir = get_order_dir();
    row = get_number_from_file(dir + "last_row");
    file = std::ifstream(dir + "orders");
    if (file.good()) {
        parse_line();
    }
}

void InternetOrders::parse_line() {
    unsigned int rose;
    unsigned int tulip;
    file >> rose >> tulip;
    if (!file.fail()) {
        current_order = Order(rose, tulip);
        row++;
    } else {
        current_order = NullOrder();
    }
}

Order& InternetOrders::get_current_order() {
    if (current_order.isFulfilled()) {
        parse_line();
    }

    return current_order;
}

std::string InternetOrders::get_order_dir() {
    std::ostringstream path;
    path << orders_dir << chain_id << "/";
    return path.str();
}

InternetOrders::~InternetOrders() {
    std::string path = get_order_dir() + "last_row";
    std::fstream stream(path);
    stream << row;  // Esto NO anda, no se por qué
}

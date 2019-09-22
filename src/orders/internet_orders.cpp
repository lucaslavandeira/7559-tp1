#include <sstream>
#include <iostream>
#include "internet_orders.h"
#include "NullOrder.h"
#include "../util/get_number_from_file.h"
#include "../util/create_directory_if_not_exists.h"

InternetOrders::InternetOrders(int chain_id, const std::string orders_dir) :
        chain_id(chain_id),
        orders_dir(orders_dir),
        row(0),
        current_order(NullOrder()) {
    const std::string& dir = get_order_dir();
    create_directory_if_not_exists(dir);
    row = get_number_from_file(dir + "last_row");
    file = std::ifstream(dir + "orders");
    unsigned int start_row = 0;
    while(file.good() && start_row <= row) {
        parse_line();
        start_row++;
    }
}

void InternetOrders::parse_line() {
    unsigned int rose;
    unsigned int tulip;
    file >> rose >> tulip;
    if (!file.fail()) {
        current_order = Order(rose, tulip);
    } else {
        current_order = NullOrder();
    }
}

Order& InternetOrders::get_current_order() {
    if (current_order.isFulfilled()) {
        parse_line();
        row++;
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
    std::ofstream stream(path);

    stream << row;
}

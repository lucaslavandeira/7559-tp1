#ifndef BOUQUET_STOCK_SELLS_H
#define BOUQUET_STOCK_SELLS_H

#include <vector>
#include "flower_bouquet.h"
#include "orders/Order.h"
#include <string>
#include <unordered_map>
#include <queue>
#include "bouquet_stock.h"

class BouquetStockSells : public BouquetStock {
public:
    BouquetStockSells(int chain_id, const std::string& save_route);

    ~BouquetStockSells();
    /*
    Check if the stock is enough to fulfill an order
    */
    bool can_fulfill_order(const Order& order);
    /*
    Extracts the number of flowers from the order out of the stock
    If there is no such ammount of flowers, throws NotEnoughBouquetError exception
    */
    std::vector<FlowerBouquet> extract_flowers(Order& order);
};

#endif

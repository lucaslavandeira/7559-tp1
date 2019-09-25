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

    bool can_fulfill_order(const Order& order);
    std::vector<FlowerBouquet> extract_flowers(Order& order);
};

#endif

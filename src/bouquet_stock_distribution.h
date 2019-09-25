#ifndef BOUQUET_STOCK_DISTRIBUTION_H
#define BOUQUET_STOCK_DISTRIBUTION_H

#include <vector>
#include "flower_bouquet.h"
#include "orders/Order.h"
#include <string>
#include <unordered_map>
#include <queue>
#include "bouquet_stock.h"

class BouquetStockDistribution : public BouquetStock {
public:
    BouquetStockDistribution(int chain_id, const std::string& save_route);

    ~BouquetStockDistribution();

    std::vector<FlowerBouquet> extract_flowers(std::string type, int ammount);
};

#endif

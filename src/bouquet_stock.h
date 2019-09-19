#ifndef BOUQUET_STOCK_H
#define BOUQUET_STOCK_H

#include <vector>
#include "flower_bouquet.h"
#include <string>
#include <unordered_map>

#define FLOWERS_FILE_NAME "flowers"

class BouquetStock {
private:
    int chain_id;
    std::unordered_map<std::string, std::vector<FlowerBouquet>> flowers;
    std::string save_route;

    std::string flower_path(const std::string &type) const;
public:
    BouquetStock(int chain_id, std::string save_route);
    void init_stock();
    void save_stock();
    void add_bouquets(std::vector<FlowerBouquet> flowers);

    ~BouquetStock();
};

#endif

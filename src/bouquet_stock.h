#ifndef BOUQUET_STOCK_H
#define BOUQUET_STOCK_H

#include <vector>
#include "flower_bouquet.h"
#include <string>
#include <unordered_map>
#include <queue>

#define FLOWERS_FILE_NAME "flowers"

class BouquetStock {
private:
    int chain_id;
    std::unordered_map<std::string, std::queue<FlowerBouquet>> flowers;
    std::string save_route;

    std::string flower_path(const std::string &type) const;
public:
    BouquetStock(int chain_id, const std::string& save_route);
    void init_stock();
    void save_stock();
    void add_bouquets(const std::vector<FlowerBouquet>& flowers);

    ~BouquetStock();

    unsigned int stock_of_type(const std::string& type);
    std::vector<FlowerBouquet> get_flowers(unsigned int rose_amount, unsigned int tulip_amount);
};

#endif

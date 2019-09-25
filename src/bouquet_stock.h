#ifndef BOUQUET_STOCK_H
#define BOUQUET_STOCK_H

#include <vector>
#include "flower_bouquet.h"
#include "orders/Order.h"
#include <string>
#include <unordered_map>
#include <queue>

#define FLOWERS_FILE_NAME "flowers"

class BouquetStock {
private:
    int chain_id;
    std::string save_route;

    std::string flower_path(const std::string &type) const;
protected:
    std::unordered_map<std::string, std::queue<FlowerBouquet>> flowers;
public:
    BouquetStock(int chain_id, const std::string& save_route);
    /*
    Loads the stock (if exists) from file
    */    
    void init_stock();
    /*
    Saves the stock into a file
    */    
    void save_stock();
    /*
    Add bouquets to the stock
    */   
    void add_bouquets(const std::vector<FlowerBouquet>& flowers);

    ~BouquetStock();
    /*
    Returns the ammount of flowers of type "type" that are in the current stock
    */
    unsigned int stock_of_type(const std::string& type);
};

#endif

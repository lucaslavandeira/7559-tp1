#include "bouquet_stock_distribution.h"
#include "flower_bouquet.h"
#include "exceptions/NotEnoughBouquetsError.h"
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <queue>
#include <fstream>

BouquetStockDistribution::BouquetStockDistribution(int chain_id, const std::string& save_route)
 : BouquetStock(chain_id, save_route) {

}

BouquetStockDistribution::~BouquetStockDistribution() {
    //this->save_stock();
}

std::vector<FlowerBouquet>
BouquetStockDistribution::extract_flowers(std::string type, int ammount) {
    if (stock_of_type(type) < (unsigned int) ammount) {
        throw NotEnoughBouquetsError(type, ammount, stock_of_type(type));
    }

    std::vector<FlowerBouquet> result;
    std::queue<FlowerBouquet>& flowers_of_type = flowers[type];

    while(result.size() < (unsigned int) ammount) {
        result.push_back(flowers_of_type.front());
        flowers_of_type.pop();
    }
    
    return result;
}

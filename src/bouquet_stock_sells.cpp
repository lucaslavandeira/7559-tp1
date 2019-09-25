#include "bouquet_stock_sells.h"
#include "flower_bouquet.h"
#include <string>
#include <vector>
#include "exceptions/NotEnoughBouquetsError.h"
#include <sstream>
#include <iostream>
#include <queue>
#include <fstream>

BouquetStockSells::BouquetStockSells(int chain_id, const std::string& save_route)
 : BouquetStock(chain_id, save_route) {

}

BouquetStockSells::~BouquetStockSells() {
    //this->save_stock();
}

std::vector<FlowerBouquet>
BouquetStockSells::extract_flowers(Order& order) {
    if (stock_of_type("rose") < order.roses) {
        throw NotEnoughBouquetsError("rose", order.roses, stock_of_type("rose"));
    }

    if (stock_of_type("tulip") < order.tulips) {
        throw NotEnoughBouquetsError("tulip", order.tulips, stock_of_type("tulip"));
    }
    std::vector<FlowerBouquet> result;
    std::queue<FlowerBouquet>& roses = flowers["rose"];
    while(result.size() < order.roses) {
        result.push_back(roses.front());
        roses.pop();
    }

    std::queue<FlowerBouquet>& tulips = flowers["tulip"];
    while(result.size() < order.roses + order.tulips) {
        result.push_back(tulips.front());
        tulips.pop();
    }
    order.markFulfilled();
    return result;
}

bool BouquetStockSells::can_fulfill_order(const Order &order) {
    return stock_of_type("rose") >= order.roses &&
        stock_of_type("tulip") >= order.tulips;
}

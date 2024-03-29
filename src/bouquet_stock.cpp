#include "bouquet_stock.h"
#include "flower_bouquet.h"
#include <string>
#include <vector>
#include "util/home_dir.h"
#include "util/get_number_from_file.h"
#include "config.h"
#include "util/create_directory_if_not_exists.h"
#include "exceptions/NotEnoughBouquetsError.h"
#include <sstream>
#include <iostream>
#include <queue>
#include <fstream>

BouquetStock::BouquetStock(int chain_id, const std::string& save_route) {
  this->chain_id = chain_id;
  this->save_route = save_route;
}

void BouquetStock::init_stock() {
    std::string stream = flower_path(this->save_route);
    this->flowers = get_flowers_from_file(stream);
}

void BouquetStock::save_stock() {
    std::basic_string<char> path = flower_path(FLOWERS_FILE_NAME);

    std::ofstream f(path);
    if (!f.good()) {
        return;
    }

    std::queue<FlowerBouquet> tmp;
    for (auto& it : this->flowers) {
        std::queue<FlowerBouquet> bouquets = it.second;
        while (!bouquets.empty()) {
            FlowerBouquet bouquet = it.second.front();
            f << it.first << " " << bouquet.productor_id << std::endl;
            tmp.push(bouquets.front());
            bouquets.pop();
        }
        it.second = tmp;
    }
}

void BouquetStock::add_bouquets(const std::vector<FlowerBouquet>& bouquets) {
    for (auto & bouquet : bouquets) {
      this->flowers[bouquet.type].push(bouquet);
    }
}

std::string BouquetStock::flower_path(const std::string &type) const {
    const char* home = home_dir();
    std::stringstream stream;

    stream << home << "/" << CONFIG_PATH << "/";
    create_directory_if_not_exists(stream.str());
    stream << this->save_route << "/";
    create_directory_if_not_exists(stream.str());
    stream << chain_id << "/";
    create_directory_if_not_exists(stream.str());
    stream << FLOWERS_FILE_NAME;

    return stream.str();
}

BouquetStock::~BouquetStock() {
    //this->save_stock();
}

unsigned int BouquetStock::stock_of_type(const std::string &type) {
    return flowers[type].size();
}

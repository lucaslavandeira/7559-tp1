#include "bouquet_stock.h"
#include "flower_bouquet.h"
#include <string>
#include <vector>
#include <unordered_map>
#include "util/home_dir.h"
#include "util/get_number_from_file.h"
#include "config.h"
#include "util/create_directory_if_not_exists.h"
#include <sstream>
#include <iostream>
#include <fstream>

BouquetStock::BouquetStock(int chain_id, std::string save_route) {
  this->chain_id = chain_id;
  this->save_route = save_route;
}

void BouquetStock::init_stock() {
    std::string stream = flower_path(this->save_route);
    this->flowers = get_flowers_from_file(stream);

    for (auto& it : this->flowers)
        std::cout << "Cargue " << this->flowers[it.first].size() << " de " << it.first << std::endl;    
}

void BouquetStock::save_stock() {
    std::basic_string<char> path = flower_path(FLOWERS_FILE_NAME);

    std::ofstream f(path);
    if (!f.good()) {
        std::cout << "No se abrió bien el file" << path << std::endl;
        return;
    }

    for (auto& it : this->flowers) {
        for (int i = 0; i < (int) this->flowers[it.first].size(); i++) {
            f << it.first << " " << this->flowers[it.first][i].productor_id << std::endl;
        }
    }  
}

void BouquetStock::add_bouquets(std::vector<FlowerBouquet> bouquets) {
    for (int i = 0; i < (int) bouquets.size(); i++) {
      this->flowers[bouquets[i].type].push_back(bouquets[i]);
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

#include "statistics_center.h"
#include "../notifications/statistics_notification.h"
#include <iostream>
#include <fcntl.h> 
#include <zconf.h>
#include <sys/stat.h>
#include "../util/home_dir.h"
#include "../config.h"
#include <sstream>
#include <fstream>
#include "../util/create_directory_if_not_exists.h"

#define STATISTICS_MSG "s"
#define EXIT_MSG "c"
#define STATISTICS_CENTER_DIR_NAME "statistics_center"
#define PRODUCTORS_FILE_NAME "productors_statistics"
#define FLOWERS_FILE_NAME "flowers_statistics"

const std::string StatisticsCenter::no_flower_msg = "Ninguna flor fue vendida";
const std::string StatisticsCenter::no_productor_msg = "Ningun productor vendio flores";

StatisticsCenter::StatisticsCenter() {
    /*this->best_flower = no_flower_msg;
    this->best_productor = no_productor_msg;*/
    this->load_best_productor();
    this->load_best_flower();
}

void StatisticsCenter::work() {
    while (true) {
        std::vector<FlowerBouquet> sells;

        try {
            std::string msg = this->sells_route.receive_message();

            if (msg.compare(STATISTICS_MSG) == 0) {
                this->show_statistics();
                continue;
            } else if (msg.compare(EXIT_MSG) == 0) {
                break;
            }

            sells = this->sells_route.retrieve_sells();
            this->update_statistics(sells);
        } catch (int e) {
            break;
        }
    }

    this->save_statistics();
}

void StatisticsCenter::update_statistics(std::vector<FlowerBouquet> sells) {
    for (int i = 0; i < (int) sells.size(); i++) {
        if (!productors_statistics.count(sells[i].productor_id))
            productors_statistics[sells[i].productor_id] = 0;

        if (!flowers_statistics.count(sells[i].type))
            flowers_statistics[sells[i].type] = 0;  

        productors_statistics[sells[i].productor_id]++;
        flowers_statistics[sells[i].type]++;
    }

    update_best_productor();
    update_best_selling_flower();
}

void StatisticsCenter::update_best_productor() {
    int best_productor = -1;
    int sells_ammount = -1;

    for (auto& it : productors_statistics) {
        if (it.second > sells_ammount) {
            best_productor = it.first;
            sells_ammount = it.second;
        }
    }

    if (best_productor == -1) {
        this->best_productor = no_productor_msg;
        return;
    }

    this->best_productor = std::to_string(best_productor);
}

void StatisticsCenter::update_best_selling_flower() {
    std::string best_flower = "";
    int sells_ammount = -1;

    for (auto& it : flowers_statistics) {
        if (it.second > sells_ammount) {
            best_flower = it.first;
            sells_ammount = it.second;
        }
    }

    if (best_flower.compare("") == 0) {
        this->best_flower = no_flower_msg;
        return;
    }

    this->best_flower = best_flower;
}

void StatisticsCenter::show_statistics() {
    std::cout << "Productor que mas vendio: " << this->best_productor << std::endl
                << "Flor mas vendida: " << this->best_flower << std::endl;
}

void StatisticsCenter::save_statistics() {
    this->save_best_productor();
    this->save_best_flower();
}

void StatisticsCenter::save_best_productor() {
    std::basic_string<char> path_productors = this->statistics_path(PRODUCTORS_FILE_NAME);

    std::ofstream f(path_productors);

    if (!f.good()) {
        std::cout << "No se abrió bien el file" << path_productors << std::endl;
        return;
    }

    for (auto& it : this->productors_statistics) {
        f << it.first << " " << it.second << std::endl;
    }
}

void StatisticsCenter::save_best_flower() {
    std::basic_string<char> path_flowers = this->statistics_path(FLOWERS_FILE_NAME);

    std::ofstream f(path_flowers);

    if (!f.good()) {
        std::cout << "No se abrió bien el file" << path_flowers << std::endl;
        return;
    }

    for (auto& it : this->flowers_statistics) {
        f << it.first << " " << it.second << std::endl;
    }
}

std::string StatisticsCenter::statistics_path(const char* name) const {
    const char* home = home_dir();
    std::stringstream stream;

    stream << home << "/" << CONFIG_PATH << "/";
    create_directory_if_not_exists(stream.str());
    stream << STATISTICS_CENTER_DIR_NAME << "/";
    create_directory_if_not_exists(stream.str());
    stream << name;

    return stream.str();
}

void StatisticsCenter::load_best_productor() {
    struct stat buffer = {0};
    std::string path = this->statistics_path(PRODUCTORS_FILE_NAME);

    if (stat(path.c_str(), &buffer) < 0) {
        // No existe el archivo / error
        return;
    }

    std::ifstream stream(path);

    std::string line;

    while (std::getline(stream, line)) {
        std::istringstream iss(line);
        int productor_id;
        int ammount;

        if (!(iss >> productor_id >> ammount)) { break; } // error

        this->productors_statistics[productor_id] = ammount;
    }

    update_best_productor();
}

void StatisticsCenter::load_best_flower() {
    struct stat buffer = {0};
    std::string path = this->statistics_path(FLOWERS_FILE_NAME);

    if (stat(path.c_str(), &buffer) < 0) {
        // No existe el archivo / error
        return;
    }

    std::ifstream stream(path);

    std::string line;

    while (std::getline(stream, line)) {
        std::istringstream iss(line);
        std::string type;
        int ammount;

        if (!(iss >> type >> ammount)) { break; } // error

        this->flowers_statistics[type] = ammount;
    }

    update_best_selling_flower();
}

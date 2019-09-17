#include "sells_center.h"
#include "../util/home_dir.h"
#include "../util/get_number_from_file.h"
#include "../config.h"
#include "../util/create_directory_if_not_exists.h"
#include <zconf.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <sys/stat.h>

#define SELLS_CENTER_DIR_NAME "sells_center"

SellsCenter::SellsCenter(int chain_id) : chain_id(chain_id) {
    init_flower("rose");
    init_flower("tulip");
}

void SellsCenter::associate_route(DistributionRoute &distributionRoute) {
    this->route = distributionRoute;
}

FlowerPacket SellsCenter::receive() {
    FlowerPacket packet = this->route.receive();

    if (!flowers.count(packet.type)) {
        flowers[packet.type] = 0;
    }

    //Temporalmente para testear
    flowers[packet.type] = flowers[packet.type] + packet.size();

    std::cout << "Recibi " << packet.flowers.size() << " de " << packet.type << std::endl;

    return packet;
}

void SellsCenter::work() {
    while (true) {
        try {
            FlowerPacket packet = this->receive();
        } catch (int e) {
            break;
        }
        sleep(1);
    }

    save_inventory("rose");
    save_inventory("tulip");
}

void SellsCenter::init_flower(const std::string &type) {
    std::string stream = flower_path(type);
    flowers[type] = get_number_from_file(stream);

    std::cout << "Cargue " << flowers[type] << " de " << type << std::endl;
}

std::string SellsCenter::flower_path(const std::string &type) const {
    const char* home = home_dir();
    std::stringstream stream;

    stream << home << "/" << CONFIG_PATH << "/";
    create_directory_if_not_exists(stream.str());
    stream << SELLS_CENTER_DIR_NAME << "/";
    create_directory_if_not_exists(stream.str());
    stream << chain_id << "/";
    create_directory_if_not_exists(stream.str());
    stream << type;
    return stream.str();
}

void SellsCenter::save_inventory(const std::string& type) {
    std::basic_string<char> path = flower_path(type);

    std::ofstream f(path);
    if (!f.good()) {
        std::cout << "No se abrió bien el file" << path << std::endl;
        return;
    }
    f << flowers[type];
}

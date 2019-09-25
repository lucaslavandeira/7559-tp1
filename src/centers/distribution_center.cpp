#include "distribution_center.h"
#include "../flower_bouquet.h"
#include <map>
#include <vector>
#include <iostream>
#include "../util/logger.h"

#define DISTRIBUTION_CENTER_DIR_NAME "distribution_center"

DistributionCenter::DistributionCenter(int chain_id) : chain_id(chain_id), 
stock(chain_id, DISTRIBUTION_CENTER_DIR_NAME) {
    stock.init_stock();
}

void DistributionCenter::associate_send_route(DistributionRoute &route) {
    this->send_route = route;
}

void DistributionCenter::associate_receive_route(ProductionRoute &route) {
    this->recv_route = route;
}

void DistributionCenter::receive() {
    FlowerDrawer drawer = this->recv_route.receive();

    int ammount_tulips = 0;
    int ammount_roses = 0;

    for (int i = 0; i < (int) drawer.flowers.size(); i++) {
        if (drawer.flowers[i].type.compare("rose") == 0) {
            ammount_roses++;
        } else if (drawer.flowers[i].type.compare("tulip") == 0) {
            ammount_tulips++;
        }
    }

    log << "[DISTRIBUTION] [" << chain_id << "] " << "Recibi " << ammount_roses << " roses" << std::endl;
    log << "[DISTRIBUTION] [" << chain_id << "] " << "Recibi " << ammount_tulips << " tulips" << std::endl;

    this->stock.add_bouquets(drawer.flowers);
}

void DistributionCenter::transport(FlowerPacket &packet) {
    this->send_route.send(packet);
}

void DistributionCenter::work() {
    while (true) {
        try {
            this->receive();
            this->send_to_center();
        } catch(int e) {
            break;
        }
    }
    this->stock.save_stock();
    this->send_route.close();
}

void DistributionCenter::send_to_center() {
    while (this->stock.stock_of_type("rose") >= PACKET_SIZE) {
        std::vector<FlowerBouquet> send_flowers = this->stock.extract_flowers("rose", PACKET_SIZE);

        FlowerPacket packet(std::move(send_flowers), "rose");

        this->transport(packet);
    }

    while (this->stock.stock_of_type("tulip") >= PACKET_SIZE) {
        std::vector<FlowerBouquet> send_flowers = this->stock.extract_flowers("tulip", PACKET_SIZE);

        FlowerPacket packet(std::move(send_flowers), "tulip");

        this->transport(packet);        
    }
}

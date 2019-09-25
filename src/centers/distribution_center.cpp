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

    /*std::vector<FlowerBouquet> flowers_from_drawer = drawer.flowers;

    for (int i = 0; i < (int) flowers_from_drawer.size(); i++) {
        this->flowers[flowers_from_drawer[i].type].push_back(flowers_from_drawer[i]);
    }*/

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
    /*for (auto& it : this->flowers) {
        if (this->flowers[it.first].size() >= PACKET_SIZE) {
            std::vector<FlowerBouquet> send_flowers(it.second.begin(), it.second.begin() + PACKET_SIZE);

            FlowerPacket packet(std::move(send_flowers), it.first);

            this->transport(packet);

            it.second.erase(it.second.begin(), it.second.begin() + PACKET_SIZE);
        }
    }    */
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

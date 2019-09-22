#include "distribution_center.h"
#include "../flower_bouquet.h"
#include <map>
#include <vector>
#include <iostream>
#include "../util/logger.h"

DistributionCenter::DistributionCenter(int chain_id) : chain_id(chain_id) {
    this->rose_bouquets = 0;
    this->tulip_bouquets = 0;
}

void DistributionCenter::associate_send_route(DistributionRoute &route) {
    this->send_route = route;
}

void DistributionCenter::associate_receive_route(ProductionRoute &route) {
    this->recv_route = route;
}

void DistributionCenter::receive() {
    FlowerDrawer drawer = this->recv_route.receive();

    std::vector<FlowerBouquet> flowers_from_drawer = drawer.flowers;

    for (int i = 0; i < (int) flowers_from_drawer.size(); i++) {
        this->flowers[flowers_from_drawer[i].type].push_back(flowers_from_drawer[i]);
    }
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

    this->send_route.close();
}

void DistributionCenter::send_to_center() {
    for (auto& it : this->flowers) {
        if (this->flowers[it.first].size() >= PACKET_SIZE) {
            std::vector<FlowerBouquet> send_flowers(it.second.begin(), it.second.begin() + PACKET_SIZE);

            FlowerPacket packet(std::move(send_flowers), it.first);

            this->transport(packet);

            it.second.erase(it.second.begin(), it.second.begin() + PACKET_SIZE);
        }
    }    
}

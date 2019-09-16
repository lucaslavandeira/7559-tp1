#include "sells_center.h"
#include <zconf.h>

SellsCenter::SellsCenter(int chain_id) : chain_id(chain_id) {}

void SellsCenter::associate_route(DistributionRoute &distributionRoute) {
    this->route = distributionRoute;
}

FlowerPacket SellsCenter::receive() {
    FlowerPacket packet = this->route.receive();
    if (!flowers.count(packet.type)) {
        flowers[packet.type] = 0;
    }
    flowers[packet.type] = flowers[packet.type] + packet.ammount;
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
}

#include "sells_center.h"
#include "../routes/route.h"
#include <iostream>
#include <zconf.h>

SellsCenter::SellsCenter() = default;

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
            std::cout << "Hola del punto de venta! Recibí " << packet.ammount << " de " << packet.type
                      << " desde el centro!!!" << std::endl;
        } catch (int e) {
            break;
        }
        sleep(1);
    }

    std::cout << "Sells center fue cerrado!! Tenía " << flowers["tulip"] << " tulips" << std::endl;
}

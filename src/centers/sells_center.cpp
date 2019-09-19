#include "sells_center.h"
#include <zconf.h>
#include <sys/stat.h>
#include "../flower_bouquet.h"
#include "../bouquet_stock.h"
#include <iostream>
#include <fcntl.h> 

#define SELLS_CENTER_DIR_NAME "sells_center"
#define FLOWERS_FILE_NAME "flowers"

SellsCenter::SellsCenter(int chain_id) : chain_id(chain_id),
    stock(chain_id, SELLS_CENTER_DIR_NAME),
    sells_route(O_WRONLY) {
    stock.init_stock();
}

void SellsCenter::associate_route(DistributionRoute &distributionRoute) {
    this->route = distributionRoute;
}

FlowerPacket SellsCenter::receive() {
    FlowerPacket packet = this->route.receive();

    this->stock.add_bouquets(packet.flowers);

    std::cout << "Recibi " << packet.flowers.size() << " de " << packet.type << std::endl;


    //Esto deberia ir en ventas aun no diseñado (?)
    std::vector<FlowerBouquet> flowers;

    flowers = packet.flowers;

    sells_route.send_sells(flowers);

    return packet;
}

void SellsCenter::work() {
    while (true) {
        try {
            FlowerPacket packet = this->receive();
        } catch (int e) {
            break;
        }
        //sleep(5);
    }

    this->stock.save_stock();
}

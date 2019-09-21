#include "sells_center.h"
#include <zconf.h>
#include <sys/stat.h>
#include "../flower_bouquet.h"
#include "../bouquet_stock.h"
#include "../exceptions/NotEnoughBouquetsError.h"
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

    return packet;
}

void SellsCenter::work() {
    while (true) {
        try {
            FlowerPacket packet = this->receive();
        } catch (int e) {
            break;
        }
        sell();
    }

    this->stock.save_stock();
}

void SellsCenter::sell() {
    bool client_comes = (random() % 100) > 60;
    if (client_comes) {
        long tulips_amount = random() % 20;
        long roses_amount = random() % 20;

        if (stock.stock_of_type("rose") < roses_amount) {
            return;
        }

        if (stock.stock_of_type("rose") < tulips_amount) {
            return;
        }
        process_sale(roses_amount, tulips_amount);
    }
    // read from file process next sale row
}

void SellsCenter::process_sale(unsigned int rose_amount, unsigned int tulip_amount) {
    auto sale_flowers = stock.get_flowers(rose_amount, tulip_amount);
    sells_route.send_sells(sale_flowers);
}

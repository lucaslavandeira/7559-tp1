#include "sells_center.h"
#include "../exceptions/NotEnoughBouquetsError.h"
#include <iostream>

#define SELLS_CENTER_DIR_NAME "sells_center"
#define FLOWERS_FILE_NAME "flowers"
#define CLIENT_ARRIVAL_CHANCE 40  // percent

SellsCenter::SellsCenter(int chain_id, const std::string &config_path) :
        chain_id(chain_id),
        stock(chain_id, SELLS_CENTER_DIR_NAME),
        orders(chain_id, config_path + "orders/") {

    stock.init_stock();
}

void SellsCenter::associate_route(DistributionRoute &distributionRoute) {
    this->route = distributionRoute;
}

FlowerPacket SellsCenter::receive() {
    FlowerPacket packet = this->route.receive();

    this->stock.add_bouquets(packet.flowers);

    log << "[SELLS] [" << chain_id << "] " << "Recibi " << packet.flowers.size() << " de " << packet.type << " tulips" << std::endl;

    return packet;
}

void SellsCenter::work() {
    while (true) {
        try {
            FlowerPacket packet = this->receive();
        } catch (int e) {
            break;
        }
        while(sell()) {}
    }

    this->stock.save_stock();
}

bool SellsCenter::sell() {
    bool client_comes = (random() % 100) < CLIENT_ARRIVAL_CHANCE;
    if (client_comes) {
        long tulips_amount = random() % 20;
        long roses_amount = random() % 20;
        Order o(roses_amount, tulips_amount);

        if(stock.can_fulfill_order(o)) {
            process_sale(o);
            return true;
        }
        return false;
    }

    if (!orders.orders_remaining()) {
        return false;
    }

    auto& order = orders.get_current_order();
    if(stock.can_fulfill_order(order)) {
        process_sale(order);
        return true;
    }
    return false;
}

void SellsCenter::process_sale(Order &order) {
    auto sale_flowers = stock.extract_flowers(order);

    int ammount_tulips = 0;
    int ammount_roses = 0;

    for (int i = 0; i < (int) sale_flowers.size(); i++) {
        if (sale_flowers[i].type.compare("rose") == 0) {
            ammount_roses++;
        } else if (sale_flowers[i].type.compare("tulip") == 0) {
            ammount_tulips++;
        }
    }

    log << "[SELLS] [" << chain_id << "] " << "Vendi " << ammount_roses << " roses" << std::endl;
    log << "[SELLS] [" << chain_id << "] " << "Vendi " << ammount_tulips << " tulips" << std::endl;

    sells_route.send_sells(sale_flowers);
}

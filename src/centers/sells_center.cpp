#include "sells_center.h"
#include "../bouquet_stock.h"
#include "../exceptions/NotEnoughBouquetsError.h"
#include "../orders/internet_orders.h"
#include "../util/home_dir.h"
#include <iostream>
#include <fcntl.h>
#include <sstream>

#define SELLS_CENTER_DIR_NAME "sells_center"
#define FLOWERS_FILE_NAME "flowers"
#define CLIENT_ARRIVAL_CHANCE 60  // percent

SellsCenter::SellsCenter(int chain_id, const std::string& config_path) :
        chain_id(chain_id),
        stock(chain_id, SELLS_CENTER_DIR_NAME),
        sells_route(O_WRONLY),
        orders(chain_id, config_path + "orders/") {

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
    bool client_comes = (random() % 100) < CLIENT_ARRIVAL_CHANCE;
    if (client_comes) {
        long tulips_amount = random() % 20;
        long roses_amount = random() % 20;
        Order o(roses_amount, tulips_amount);

        if(stock.can_fulfill_order(o)) {
            process_sale(o);
        }
        return;
    }
    auto& order = orders.get_current_order();
    if(stock.can_fulfill_order(order)) {
        process_sale(order);
    }
}

void SellsCenter::process_sale(Order& order) {
    auto sale_flowers = stock.extract_flowers(order);
    sells_route.send_sells(sale_flowers);
}

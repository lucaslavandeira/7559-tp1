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
            process_sale(o, false);
            return true;
        }
        return false;
    }

    if (!orders.orders_remaining()) {
        return false;
    }

    auto& order = orders.get_current_order();
    if(stock.can_fulfill_order(order)) {
        process_sale(order, true);
        return true;
    }
    return false;
}

void SellsCenter::process_sale(Order &order, bool make_ticket) {
    auto sale_flowers = stock.extract_flowers(order);

    if (make_ticket)
        this->make_ticket(sale_flowers);

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

void SellsCenter::make_ticket(std::vector<FlowerBouquet>& flowers) {
    std::unordered_map<int, int> roses_by_productor;
    std::unordered_map<int, int> tulips_by_productor;

    int total_flowers = flowers.size();

    for (int i = 0; i < total_flowers; i++) {
        if (flowers[i].type.compare("rose") == 0)
            roses_by_productor[flowers[i].productor_id]++;
        else if (flowers[i].type.compare("tulip") == 0)
            tulips_by_productor[flowers[i].productor_id]++;
    }

    log << "---------TICKET DE COMPRA-----------" << std::endl;
    log << "Se vendieron un total de " << total_flowers << " flores" << std::endl;

    int total_roses = 0;

    for (auto& it : roses_by_productor) {
        log << it.second << " rosas del productor " << it.first << std::endl;
        total_roses += it.second;
    }

    log << "Con un total de " << total_roses << " rosas" << std::endl;

    int total_tulips = 0;

    for (auto& it : tulips_by_productor) {
        log << it.second << " tulipanes del productor " << it.first << std::endl;
        total_tulips += it.second;
    }

    log << "Con un total de " << total_tulips << " tulipanes" << std::endl;
    log << "---------FIN DE TICKET DE COMPRA-----------" << std::endl;
}

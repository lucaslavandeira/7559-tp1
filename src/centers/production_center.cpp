#include "production_center.h"
#include "../routes/production_route.h"
#include <random>
#include <iostream>
#include <zconf.h>
#include "../flower_drawer.h"
#include "../ipc/ExitFlag.h"
#include "../flower_bouquet.h"
#include "../util/logger.h"

ProductionCenter::ProductionCenter(int chain_id) : chain_id(chain_id) {
    srand(time(NULL));
}

FlowerDrawer ProductionCenter::harvest() {
    int ammount_rose_bouquets = rand() % BOUQUET_PRODUCTION;

    int ammount_tulips_bouquets = BOUQUET_PRODUCTION - ammount_rose_bouquets;

    std::vector<FlowerBouquet> flowers;

    log << "[" << chain_id << "] " << "Se produjeron " << ammount_rose_bouquets << " rosas" << std::endl;
    //log << "[" << chain_id << "] " << "Se produjeron " << ammount_tulips_bouquets << " tulips";

    for (int i = 0; i < ammount_rose_bouquets; i++) {
        flowers.push_back(FlowerBouquet("rose", this->chain_id));
    }

    for (int i = 0; i < ammount_tulips_bouquets; i++) {
        flowers.push_back(FlowerBouquet("tulip", this->chain_id));
    }

    return FlowerDrawer(std::move(flowers), this->chain_id);
}

void ProductionCenter::associate_route(ProductionRoute &route) {
    this->route = route;
}

void ProductionCenter::transport(FlowerDrawer drawer) {
    this->route.send(drawer);
}

void ProductionCenter::work() {
    ExitFlag flag;
    while (flag.read()) {
        FlowerDrawer drawer = harvest();

        this->transport(drawer);
        usleep(250000);
    }
    this->route.close();
}

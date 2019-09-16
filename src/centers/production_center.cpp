#include "production_center.h"
#include "../routes/production_route.h"
#include <random>
#include <iostream>
#include <zconf.h>
#include "../flower_drawer.h"
#include "../ipc/ExitFlag.h"

ProductionCenter::ProductionCenter(int chain_id) : chain_id(chain_id) {
    srand(time(NULL));
}

FlowerDrawer ProductionCenter::harvest() {
    int ammount_rose_bouquets = rand() % BOUQUET_PRODUCTION;

    int ammount_tulips_bouquets = BOUQUET_PRODUCTION - ammount_rose_bouquets;

    return FlowerDrawer(ammount_rose_bouquets, ammount_tulips_bouquets);
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
        sleep(1);
    }
    this->route.close();
}

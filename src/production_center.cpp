#include "production_center.h"
#include "production_route.h"
#include <random>
#include <iostream>
#include "flower_drawer.h"

ProductionCenter::ProductionCenter() {
  srand(time(NULL));
  this->stock_bouquet = 0;
}

FlowerDrawer ProductionCenter::harvest() {
  int ammount_rose_bouquets = rand() % BOUQUET_PRODUCTION;

  int ammount_tulips_bouquets = BOUQUET_PRODUCTION - ammount_rose_bouquets;

  return FlowerDrawer(ammount_rose_bouquets, ammount_tulips_bouquets);
}

void ProductionCenter::associate_route(ProductionRoute& route) {
  this->route = route;
}

void ProductionCenter::transport(FlowerDrawer drawer) {
  this->route.send(drawer);
}

void ProductionCenter::work() {
  while(true) {
    FlowerDrawer drawer = ProductionCenter().harvest();

    this->transport(drawer);

    break;
  }

  std::cout << "Production center fue cerrado!!" << std::endl;
}

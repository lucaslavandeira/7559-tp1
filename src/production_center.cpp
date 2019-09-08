#include "production_center.h"
#include "route.h"
#include <iostream>

ProductionCenter::ProductionCenter() {
  this->stock_bouquet = 0;
}

int ProductionCenter::harvest() {
  return 40;
}

void ProductionCenter::associate_route(Route& route) {
  this->route = route;
}

void ProductionCenter::transport(int bouquets) {
  this->route.send(bouquets);
}

void ProductionCenter::work() {
  while(true) {
    int harvest = ProductionCenter().harvest();

    this->transport(harvest);

    break;
  }

  std::cout << "Production center fue cerrado!!" << std::endl;
}

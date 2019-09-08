#include "sells_center.h"
#include "route.h"
#include <iostream>

SellsCenter::SellsCenter() {
}

void SellsCenter::associate_route(Route& route) {
  this->route = route;
}

int SellsCenter::receive() {
  return this->route.receive();
}

void SellsCenter::work() {
  int bouquets = this->receive();

  std::cout << "Hola del punto de venta! Recibí " << bouquets << " desde el centro!!!" << std::endl;
}

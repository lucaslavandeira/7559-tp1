#include "sells_center.h"
#include "route.h"
#include <iostream>
#include <zconf.h>

SellsCenter::SellsCenter() {
}

void SellsCenter::associate_route(DistributionRoute& route) {
  this->route = route;
}

FlowerPacket SellsCenter::receive() {
  return this->route.receive();
}

void SellsCenter::work() {
  //Sleep para recibir todo - Temporal
  int i = 0;
  while (i < 5) {
    FlowerPacket packet = this->receive();
    std::cout << "Hola del punto de venta! Recibí " << packet.ammount << " de " << packet.type << " desde el centro!!!" << std::endl;
    i++;
    sleep(1);
  }

  std::cout << "Sells center fue cerrado!!" << std::endl;
}

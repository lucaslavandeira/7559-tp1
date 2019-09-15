#include "sells_center.h"
#include "route.h"
#include "ipc/ExitFlag.h"
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
  ExitFlag flag;
  while (flag.read()) {
    FlowerPacket packet = this->receive();
    std::cout << "Hola del punto de venta! Recibí " << packet.ammount << " de " << packet.type << " desde el centro!!!" << std::endl;
    sleep(1);
  }

  std::cout << "Sells center fue cerrado!!" << std::endl;
}

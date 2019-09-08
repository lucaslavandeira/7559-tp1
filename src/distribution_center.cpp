#include "distribution_center.h"
#include "route.h"
#include <iostream>

DistributionCenter::DistributionCenter() {
}

void DistributionCenter::associate_send_route(Route& route) {
  this->send_route = route;
}

void DistributionCenter::associate_receive_route(Route& route) {
  this->recv_route = route;
}

void DistributionCenter::receive() {
  this->bouquets = this->recv_route.receive();
}

void DistributionCenter::transport() {
  this->send_route.send(this->bouquets);
}

void DistributionCenter::work() {
  while(true) {
    this->receive();

    this->transport();

    break;
  }

  std::cout << "Distribution center fue cerrado!!" << std::endl;
}

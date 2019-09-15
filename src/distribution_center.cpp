#include "distribution_center.h"
#include "route.h"
#include <iostream>
#include "flower_drawer.h"
#include "flower_packet.h"
#include "ipc/ExitFlag.h"

DistributionCenter::DistributionCenter() {
  this->rose_bouquets = 0;
  this->tulip_bouquets = 0;
}

void DistributionCenter::associate_send_route(DistributionRoute& route) {
  this->send_route = route;
}

void DistributionCenter::associate_receive_route(ProductionRoute& route) {
  this->recv_route = route;
}

void DistributionCenter::receive() {
  FlowerDrawer drawer = this->recv_route.receive();

  this->rose_bouquets += drawer.rose_bouquets;
  this->tulip_bouquets += drawer.tulip_bouquets;

  while (this->rose_bouquets >= PACKET_SIZE) {
    this->rose_bouquets -= PACKET_SIZE;
    FlowerPacket packet(PACKET_SIZE, "rose");
    this->transport(packet);
  }

  while (this->tulip_bouquets >= PACKET_SIZE) {
    this->tulip_bouquets -= PACKET_SIZE;
    FlowerPacket packet(PACKET_SIZE, "tulip");
    this->transport(packet);
  }
}

void DistributionCenter::transport(FlowerPacket& packet) {
  this->send_route.send(packet);
}

void DistributionCenter::work() {
  ExitFlag flag;
  while(flag.read()) {
    this->receive();
  }

  std::cout << "Distribution center fue cerrado!!" << std::endl;
}

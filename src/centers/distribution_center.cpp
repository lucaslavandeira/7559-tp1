#include "distribution_center.h"


DistributionCenter::DistributionCenter(int chain_id) : chain_id(chain_id) {
    this->rose_bouquets = 0;
    this->tulip_bouquets = 0;
}

void DistributionCenter::associate_send_route(DistributionRoute &route) {
    this->send_route = route;
}

void DistributionCenter::associate_receive_route(ProductionRoute &route) {
    this->recv_route = route;
}

void DistributionCenter::receive() {
  FlowerDrawer drawer = this->recv_route.receive();

  this->rose_bouquets += drawer.rose_bouquets;
  this->tulip_bouquets += drawer.tulip_bouquets;
}

void DistributionCenter::transport(FlowerPacket &packet) {
    this->send_route.send(packet);
}

void DistributionCenter::work() {
    while (true) {
        try {
            this->receive();
            this->send_to_center();
        } catch(int e) {
            break;
        }
    }

    this->send_route.close();
}

void DistributionCenter::send_to_center() {
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

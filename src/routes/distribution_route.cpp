#include "distribution_route.h"
#include "route.h"
#include "../flower_packet.h"
#include "../flower_bouquet.h"
#include <string>
#include <iostream>

const std::string DistributionRoute::send_msg = "Packet sent";
const std::string DistributionRoute::close_msg = "Close";

DistributionRoute::DistributionRoute() : route(close_msg) {

}

void DistributionRoute::send(FlowerPacket& packet) {
  this->route.send(send_msg, send_msg.size());

  std::string type = packet.type;

  this->route.send(type, type.size());

  std::string packet_size = std::to_string(packet.size());

  this->route.send(packet_size, packet_size.size());

  std::vector<FlowerBouquet> flowers = packet.flowers;

  for (int i = 0; i < packet.size(); i++) {
    std::string productor = std::to_string(flowers[i].productor_id);

    this->route.send(productor, productor.size());
  }
}

FlowerPacket DistributionRoute::receive() {
  std::string msg = this->route.receive();

  if (msg.compare(close_msg) == 0) {
    throw 1;
  }

  std::string type = this->route.receive();

  int packet_size = std::stoi(this->route.receive());

  std::vector<FlowerBouquet> flowers;

  for (int i = 0; i < packet_size; i++) {
    int productor_id = std::stoi(this->route.receive());

    flowers.push_back(FlowerBouquet(type, productor_id));
  }

  return FlowerPacket(std::move(flowers), type);
}

void DistributionRoute::close() {
    this->route.send(close_msg, close_msg.size());
}

#include "distribution_route.h"
#include "route.h"
#include "../flower_packet.h"
#include <string>

DistributionRoute::DistributionRoute() {

}

void DistributionRoute::send(FlowerPacket& packet) {
  std::string type = packet.type;

  std::string ammount = std::to_string(packet.ammount);

  this->route.send(type, type.size());
  this->route.send(ammount, ammount.size());
}

FlowerPacket DistributionRoute::receive() {
  std::string type = this->route.receive();
  if (type == "close") {
      throw 1;
  }

  std::string ammount = this->route.receive();
  if (type == "close") {
      throw 1;
  }
  return FlowerPacket(std::stoi(ammount), type);
}

void DistributionRoute::close() {
    this->route.close();
}

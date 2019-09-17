#include "flower_packet.h"
#include <vector>
#include "flower_bouquet.h"
#include <string>

FlowerPacket::FlowerPacket(std::vector<FlowerBouquet> flowers, std::string type) {
  //Hay que agregar validaciones

  this->flowers = flowers;
  this->type = type;
}

int FlowerPacket::size() {
  return PACKET_SIZE;
}

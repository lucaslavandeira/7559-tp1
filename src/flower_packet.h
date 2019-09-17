#ifndef FLOWER_PACKET_H
#define FLOWER_PACKET_H

#include <string>
#include <vector>
#include "flower_bouquet.h"

#define PACKET_SIZE 2

class FlowerPacket {
public:
  std::vector<FlowerBouquet> flowers;
  std::string type;

  FlowerPacket(std::vector<FlowerBouquet> flowers, std::string type);
  int size();
};

#endif

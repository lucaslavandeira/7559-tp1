#ifndef FLOWER_PACKET_H
#define FLOWER_PACKET_H

#include <string>

class FlowerPacket {
public:
  int ammount;
  std::string type;

  FlowerPacket(int ammount, std::string type);
};

#endif

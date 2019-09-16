#ifndef SELLS_CENTER_H
#define SELLS_CENTER_H

#include <unordered_map>
#include <string>
#include "../routes/distribution_route.h"

class SellsCenter {
    std::unordered_map<std::string, int> flowers;
public:
  DistributionRoute route;

  SellsCenter();
  void associate_route(DistributionRoute& distributionRoute);
  void work();

private:
    FlowerPacket receive();
};

#endif

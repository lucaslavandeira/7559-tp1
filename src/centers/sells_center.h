#ifndef SELLS_CENTER_H
#define SELLS_CENTER_H

#include <unordered_map>
#include <string>
#include "../routes/distribution_route.h"

class SellsCenter {
    int chain_id;
    std::unordered_map<std::string, int> flowers;
public:
  DistributionRoute route;

  explicit SellsCenter(int chain_id);
  void associate_route(DistributionRoute& distributionRoute);
  void work();

private:
    FlowerPacket receive();
};

#endif

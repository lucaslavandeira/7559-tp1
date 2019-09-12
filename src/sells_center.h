#ifndef SELLS_CENTER_H
#define SELLS_CENTER_H

#include "distribution_route.h"

class SellsCenter {
public:
  DistributionRoute route;

  SellsCenter();
  void associate_route(DistributionRoute& route);
  FlowerPacket receive();
  void work();
};

#endif

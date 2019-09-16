#ifndef DISTRIBUTION_ROUTE_H
#define DISTRIBUTION_ROUTE_H

#include "route.h"
#include "../flower_packet.h"

class DistributionRoute {
private:
  Route route;
public:
  DistributionRoute();
  void send(FlowerPacket& packet);
  FlowerPacket receive();
  void close();
};

#endif

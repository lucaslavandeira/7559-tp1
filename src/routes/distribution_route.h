#ifndef DISTRIBUTION_ROUTE_H
#define DISTRIBUTION_ROUTE_H

#include "route.h"
#include "../flower_packet.h"

class DistributionRoute {
private:
  static const std::string send_msg;
  static const std::string close_msg;
  Route route;
public:
  DistributionRoute();
  void send(FlowerPacket& packet);
  FlowerPacket receive();
  void close();
};

#endif

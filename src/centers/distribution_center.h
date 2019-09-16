#ifndef DISTRIBUTION_CENTER_H
#define DISTRIBUTION_CENTER_H

#include "../routes/production_route.h"
#include "../routes/distribution_route.h"
#include "../flower_drawer.h"
#include "../flower_packet.h"

#define PACKET_SIZE 2

class DistributionCenter {
public:
  DistributionRoute send_route;
  ProductionRoute recv_route;
  int rose_bouquets;
  int tulip_bouquets;

  DistributionCenter();
  void receive();
  void transport(FlowerPacket& packet);
  void associate_receive_route(ProductionRoute& route);
  void associate_send_route(DistributionRoute& route);
  void work();
};

#endif

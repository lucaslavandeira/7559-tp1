#ifndef DISTRIBUTION_CENTER_H
#define DISTRIBUTION_CENTER_H

#include <unordered_map>
#include "../routes/production_route.h"
#include "../routes/distribution_route.h"
#include "../flower_drawer.h"
#include "../flower_packet.h"

#define PACKET_SIZE 2

class DistributionCenter {
    int chain_id;
    std::unordered_map<std::string, int> flowers;
public:
  DistributionRoute send_route;
  ProductionRoute recv_route;
  int rose_bouquets;
  int tulip_bouquets;

  explicit DistributionCenter(int chain_id);
  void receive();
  void send_to_center();

  void associate_receive_route(ProductionRoute& route);
  void associate_send_route(DistributionRoute& route);
  void work();

private:
    void transport(FlowerPacket& packet);

};

#endif

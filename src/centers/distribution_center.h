#ifndef DISTRIBUTION_CENTER_H
#define DISTRIBUTION_CENTER_H

#include <unordered_map>
#include "../routes/production_route.h"
#include "../routes/distribution_route.h"
#include "../flower_drawer.h"
#include "../flower_packet.h"
#include "../flower_bouquet.h"
#include <vector>
#include "../util/logger.h"
#include "../bouquet_stock_distribution.h"

class DistributionCenter {
    int chain_id;
    Logger log;
    BouquetStockDistribution stock;
    std::unordered_map<std::string, std::vector<FlowerBouquet>> flowers;

public:
  DistributionRoute send_route;
  ProductionRoute recv_route;

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

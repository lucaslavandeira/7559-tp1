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
  /*
  Method to receive bouquets from the production center
  */
  void receive();
  /*
  Method to send bouquets to the sells center
  */
  void send_to_center();
  /*
  Associates this distribution center to a production center
  Everything sent through the production center will arrive here
  */
  void associate_receive_route(ProductionRoute& route);
  /*
  Associates this distribution center to a sells center
  Everything sent through the distribution center will arrive to a sells center
  */
  void associate_send_route(DistributionRoute& route);
  /*
  Distribution center loop for working
  */
  void work();

private:
    void transport(FlowerPacket& packet);

};

#endif

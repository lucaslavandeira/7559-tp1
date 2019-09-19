#ifndef SELLS_CENTER_H
#define SELLS_CENTER_H

#include <unordered_map>
#include <string>
#include "../routes/distribution_route.h"
#include "../flower_bouquet.h"
#include "../bouquet_stock.h"
#include "../ipc/sells_route.h"

class SellsCenter {
private:
    int chain_id;
    BouquetStock stock;
    SellsRoute sells_route;
    //std::unordered_map<std::string, int> flowers;
    std::unordered_map<std::string, std::vector<FlowerBouquet>> flowers;

    FlowerPacket receive();

public:
  DistributionRoute route;

  explicit SellsCenter(int chain_id);
  void associate_route(DistributionRoute& distributionRoute);
  void work();
};

#endif

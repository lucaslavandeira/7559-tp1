#ifndef SELLS_CENTER_H
#define SELLS_CENTER_H

#include <unordered_map>
#include <string>
#include "../routes/distribution_route.h"
#include "../flower_bouquet.h"
#include "../bouquet_stock.h"
#include "../notifications/sells_notification.h"
#include "../orders/internet_orders.h"
#include "../util/logger.h"

class SellsCenter {
private:
    int chain_id;
    BouquetStock stock;
    SellsNotification sells_route;
    //std::unordered_map<std::string, int> flowers;
    std::unordered_map<std::string, std::vector<FlowerBouquet>> flowers;
    InternetOrders orders;
    Logger log;

public:
  DistributionRoute route;

  SellsCenter(int chain_id, const std::string& config_path);
  void associate_route(DistributionRoute& distributionRoute);
  void work();

private:
    FlowerPacket receive();
    void sell();
    void process_sale(Order& order);
};

#endif

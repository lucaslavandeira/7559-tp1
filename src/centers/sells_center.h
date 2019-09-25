#ifndef SELLS_CENTER_H
#define SELLS_CENTER_H

#include <unordered_map>
#include <string>
#include "../routes/distribution_route.h"
#include "../flower_bouquet.h"
#include "../bouquet_stock_sells.h"
#include "../notifications/sells_notification.h"
#include "../orders/internet_orders.h"
#include "../util/logger.h"

class SellsCenter {
private:
    int chain_id;
    BouquetStockSells stock;
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
    bool sell();
    void process_sale(Order& order, bool make_ticket);
    void make_ticket(std::vector<FlowerBouquet>& flowers);
};

#endif

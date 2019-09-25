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
    /*
    Associates this sells center with a distribution center
    */
    void associate_route(DistributionRoute& distributionRoute);
    /*
    Work loop
    */
    void work();

private:
    /*
    Method to receive flowers from the associated distribution center
    */
    FlowerPacket receive();
    /*
    Method to create sells
    Returns false if sell can't be done
    Otherwise returns true
    */    
    bool sell();
    /*
    Process an order sale and sends info to the statistics center
    */
    void process_sale(Order& order, bool make_ticket);
    /*
    Logs a ticket of sold flowers
    */
    void make_ticket(std::vector<FlowerBouquet>& flowers);
};

#endif

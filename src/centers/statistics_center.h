#ifndef STATISTICS_CENTER_H
#define STATISTICS_CENTER_H

#include "../notifications/statistics_notification.h"
#include <vector>
#include "../flower_bouquet.h"
#include <unordered_map>

class StatisticsCenter {
private:
    std::unordered_map<int, int> productors_statistics;
    std::unordered_map<std::string, int> flowers_statistics;
    std::string best_flower;
    std::string best_productor;

    StatisticsNotification sells_route;

    void update_statistics(std::vector<FlowerBouquet> sells);
    void update_best_productor();
    void update_best_selling_flower();
    void show_statistics();
public:
    StatisticsCenter();
    void work();
};

#endif

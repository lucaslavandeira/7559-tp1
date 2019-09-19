#ifndef STATISTICS_CENTER_H
#define STATISTICS_CENTER_H

#include "../ipc/sells_route.h"
#include <vector>
#include "../flower_bouquet.h"

class StatisticsCenter {
private:
    std::unordered_map<int, int> productors_statistics;
    std::unordered_map<std::string, int> flowers_statistics;

    SellsRoute sells_route;

    void update_statistics(std::vector<FlowerBouquet> sells);
    void update_best_productor();
    void update_best_selling_flower();
public:
    StatisticsCenter();
    void work();
};

#endif

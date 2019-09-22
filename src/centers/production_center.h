#ifndef PRODUCTION_CENTER_H
#define PRODUCTION_CENTER_H

#include "../routes/production_route.h"
#include "../flower_drawer.h"
#include "../util/logger.h"

#define BOUQUET_PRODUCTION 10

class ProductionCenter {
    int chain_id;
    Logger log;
public:
    ProductionRoute route;

    explicit ProductionCenter(int chain_id);

    void associate_route(ProductionRoute &route);

    void transport(FlowerDrawer drawer);

    FlowerDrawer harvest();

    void work();
};

#endif

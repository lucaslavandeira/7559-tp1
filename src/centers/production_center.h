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
    /*
    Associates this production center with a distribution center
    */
    void associate_route(ProductionRoute &route);
    /*
    Transport drawers of flowers to the associated distribution center
    */
    void transport(FlowerDrawer drawer);
    /*
    Produces BOUQUET_PRODUCTION flowers
    */
    FlowerDrawer harvest();
    /*
    Work loop
    */
    void work();
};

#endif

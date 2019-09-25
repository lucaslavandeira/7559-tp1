#ifndef PRODUCTION_ROUTE_H
#define PRODUCTION_ROUTE_H

#include "route.h"
#include "../flower_drawer.h"
#include <string>

class ProductionRoute {
private:
    static const std::string send_msg;
    static const std::string close_msg;
    Route route;
public:
    ProductionRoute();
    /*
    Sends a drawer of bouquets through the route to a distribution center
    */    
    void send(FlowerDrawer& drawer);
    /*
    Receives a drawer of bouquets from a production center
    */
    FlowerDrawer receive();
    /*
    Sends a close message to a distribution center
    */    
    void close();
};

#endif

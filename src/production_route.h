#ifndef PRODUCTION_ROUTE_H
#define PRODUCTION_ROUTE_H

#include "route.h"
#include "flower_drawer.h"

class ProductionRoute {
private:
  Route route;
public:
  ProductionRoute();
  void send(FlowerDrawer& drawer);
  FlowerDrawer receive();
  void close();
};

#endif

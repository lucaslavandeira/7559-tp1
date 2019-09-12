#ifndef PRODUCTION_CENTER_H
#define PRODUCTION_CENTER_H

#include "production_route.h"
#include "flower_drawer.h"

#define BOUQUET_PRODUCTION 10

class ProductionCenter {
public:
  int stock_bouquet;
  ProductionRoute route;

  ProductionCenter();
  void associate_route(ProductionRoute& route);
  void transport(FlowerDrawer drawer);
  FlowerDrawer harvest();
  void work();
};

#endif

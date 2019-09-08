#ifndef PRODUCTION_CENTER_H
#define PRODUCTION_CENTER_H

#include "route.h"

class ProductionCenter {
public:
  int stock_bouquet;
  Route route;

  ProductionCenter();
  void associate_route(Route& route);
  void transport(int bouquets);
  int harvest();
  void work();
};

#endif

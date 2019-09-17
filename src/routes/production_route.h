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
  void send(FlowerDrawer& drawer);
  FlowerDrawer receive();
  void close();
};

#endif

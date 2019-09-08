#ifndef SELLS_CENTER_H
#define SELLS_CENTER_H

#include "route.h"

class SellsCenter {
public:
  Route route;

  SellsCenter();
  void associate_route(Route& route);
  int receive();
  void work();
};

#endif

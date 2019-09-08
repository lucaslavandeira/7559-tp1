#ifndef DISTRIBUTION_CENTER_H
#define DISTRIBUTION_CENTER_H

#include "route.h"

class DistributionCenter {
public:
  Route send_route;
  Route recv_route;
  int bouquets;

  DistributionCenter();
  void receive();
  void transport();
  void associate_receive_route(Route& route);
  void associate_send_route(Route& route);
  void work();
};

#endif

#ifndef ROUTE_H
#define ROUTE_H

class Route {
public:
  int pipefds[2];

  Route();
  void create_route(int pipefds[2]);
  void send(int bouquets);
  int receive();
  int try_receive();
  ~Route();
};

#endif

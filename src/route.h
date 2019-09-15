#ifndef ROUTE_H
#define ROUTE_H

#include <string>

#define BYTES_RECEIVE 50

class Route {
public:
  int pipefds[2];

  Route();
  void create_route(int pipefds[2]);
  void send(std::string msg, size_t size);
  std::string receive();
  ~Route();

    void close();
};

#endif

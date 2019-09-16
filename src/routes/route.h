#ifndef ROUTE_H
#define ROUTE_H

#include <string>

#define BYTES_RECEIVE 50

class Route {
    int pipefds[2]{};
public:

    Route();
    void send(const std::string &msg, size_t size);
    std::string receive();
    void close();
    ~Route();

private:
    void create_route();

};

#endif

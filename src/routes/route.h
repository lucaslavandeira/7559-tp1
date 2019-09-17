#ifndef ROUTE_H
#define ROUTE_H

#include <string>

#define BYTES_RECEIVE 50

class Route {
    int pipefds[2]{};
    std::string eof_msg;
public:
    Route(std::string eof_msg);
    void send(const std::string &msg, size_t size);
    std::string receive();
    ~Route();

private:
    void create_route();

};

#endif

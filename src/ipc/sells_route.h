#ifndef SELLS_ROUTE_H
#define SELLS_ROUTE_H

#include <vector>
#include "../flower_bouquet.h"
#include <unordered_map>

#define BYTES_RECEIVE 50

class SellsRoute {
private:
    int fd;

public:
    SellsRoute(int mode);
    ~SellsRoute();
    void delete_route();
    void send_sells(std::vector<FlowerBouquet> flowers);
    std::vector<FlowerBouquet> retrieve_sells();

    void send(const std::string &msg, size_t size);
    std::string receive();
};

#endif

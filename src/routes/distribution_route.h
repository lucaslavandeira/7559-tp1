#ifndef DISTRIBUTION_ROUTE_H
#define DISTRIBUTION_ROUTE_H

#include "route.h"
#include "../flower_packet.h"

class DistributionRoute {
private:
    static const std::string send_msg;
    static const std::string close_msg;
    Route route;
public:
    DistributionRoute();
    /*
    Sends packets of flowers through the route to a selss center
    */
    void send(FlowerPacket& packet);
    /*
    Receives packets from a distribution center
    */    
    FlowerPacket receive();
    /*
    Sends a close message through the route to a sells center
    */    
    void close();
};

#endif

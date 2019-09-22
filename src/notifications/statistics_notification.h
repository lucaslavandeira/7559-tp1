#ifndef STATISTICS_NOTIFICATION_H
#define STATISTICS_NOTIFICATION_H

#include <vector>
#include "../flower_bouquet.h"
#include "../ipc/read_fifo.h"

class StatisticsNotification {
private:
    ReadFifo fifo;
public:
    StatisticsNotification();
    std::vector<FlowerBouquet> retrieve_sells();
    std::string receive_message();
};


#endif

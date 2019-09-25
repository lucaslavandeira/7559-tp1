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
    /*
    Receives sells from distribution centers reading the Fifo
    */
    std::vector<FlowerBouquet> retrieve_sells();
    /*
    Receives messages operate:
    Normal messages: Receives sells
    Show message: Prints out information about sells
    Close: Close the statistics center
    */
    std::string receive_message();
};


#endif

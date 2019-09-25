#ifndef SELLS_NOTIFICATION_H
#define SELLS_NOTIFICATION_H

#include <vector>
#include "../flower_bouquet.h"
#include "../ipc/write_fifo.h"

#define BYTES_RECEIVE 50

class SellsNotification {
private:
    WriteFifo fifo;
public:
    SellsNotification();
    /*
    Send sells through the fifo
    */
    void send_sells(std::vector<FlowerBouquet> flowers);
    /*
    Send a close message through the Fifo to close the statisticsCenter
    */
    void send_close();
    /*
    Send a message to the statistics center to show statistics
    */
    void send_show_statistics();
};

#endif

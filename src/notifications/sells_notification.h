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
    void send_sells(std::vector<FlowerBouquet> flowers);
    void send_close();
    void send_show_statistics();
};

#endif

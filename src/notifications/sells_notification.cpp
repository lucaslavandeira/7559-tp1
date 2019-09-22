#include "sells_notification.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>
#include <unistd.h>
#include <fcntl.h> 
#include <sstream>

#define FIFO "/tmp/statistics_fifo"
#define SELLS 'n'
#define CLOSE 'c'
#define STATISTICS 's'

SellsNotification::SellsNotification() : fifo(FIFO) {

}

void SellsNotification::send_sells(std::vector<FlowerBouquet> flowers) {
    std::string msg = "";

    std::string total_flowers = std::to_string(flowers.size());

    msg += SELLS;
    msg += std::to_string(total_flowers.size());
    msg += total_flowers;
    
    for (int i = 0; i < (int) flowers.size(); i++) {
        std::string type = flowers[i].type;
        std::string productor = std::to_string(flowers[i].productor_id);

        msg += std::to_string(productor.size());
        msg += productor;

        msg += std::to_string(type.size());
        msg += type;
    }

    this->fifo.send(msg.c_str(), msg.size());
}

void SellsNotification::send_close() {
    char close = CLOSE;

    this->fifo.send(&close, 1);
}

void SellsNotification::send_show_statistics() {
    char statistics = STATISTICS;

    this->fifo.send(&statistics, 1);
}

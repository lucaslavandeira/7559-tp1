#include "sells_notification.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>
#include <unistd.h>
#include <fcntl.h> 
#include <sstream>
#include <string.h>

#define FIFO "/tmp/statistics_fifo"
#define SELLS 'n'
#define CLOSE 'c'
#define STATISTICS 's'
#define MAX_BUFFER 1000

SellsNotification::SellsNotification() : fifo(FIFO) {

}

void SellsNotification::send_sells(std::vector<FlowerBouquet> flowers) {
    char buffer[MAX_BUFFER];

    buffer[0] = SELLS;
    
    size_t total_flowers = flowers.size();

    memcpy(&buffer[1], &total_flowers, sizeof(size_t));

    int i = sizeof(size_t) + 1;

    for (int j = 0; j < (int) flowers.size(); j++) {
        int productor_id = flowers[j].productor_id;
        memcpy(&buffer[i], &productor_id, sizeof(int));

        i += sizeof(int);

        size_t size_type = flowers[j].type.size();
        memcpy(&buffer[i], &size_type, sizeof(size_t));

        i += sizeof(size_t);

        const char* type = flowers[j].type.c_str();

        memcpy(&buffer[i], type, strlen(type));

        i += strlen(type);
    }

    this->fifo.send(buffer, i);
    /*std::string msg = "";

    std::string total_flowers = std::to_string(flowers.size());

    msg += SELLS;
    msg += std::to_string(total_flowers.size());

    std::cout << "Total flowers: " << total_flowers.size() << std::endl;

    msg += total_flowers;
    
    for (int i = 0; i < (int) flowers.size(); i++) {
        std::string type = flowers[i].type;
        std::string productor = std::to_string(flowers[i].productor_id);

        msg += std::to_string(productor.size());
        msg += productor;

        msg += std::to_string(type.size());
        msg += type;
    }

    this->fifo.send(msg.c_str(), msg.size());*/
}

void SellsNotification::send_close() {
    char close = CLOSE;

    this->fifo.send(&close, 1);
}

void SellsNotification::send_show_statistics() {
    char statistics = STATISTICS;

    this->fifo.send(&statistics, 1);
}

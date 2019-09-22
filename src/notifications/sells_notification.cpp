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
#define MAX_BUFFER 2000

SellsNotification::SellsNotification() : fifo(FIFO) {

}

void SellsNotification::send_sells(std::vector<FlowerBouquet> flowers) {
    char buffer[MAX_BUFFER];

    buffer[0] = SELLS;

    size_t total_flowers = flowers.size();

    memmove(&buffer[1], &total_flowers, sizeof(size_t));

    int i = sizeof(size_t) + 1;

    for (int j = 0; j < (int) flowers.size(); j++) {
        int productor_id = flowers[j].productor_id;
        memmove(&buffer[i], &productor_id, sizeof(int));

        i += sizeof(int);

        size_t size_type = flowers[j].type.size();
        memmove(&buffer[i], &size_type, sizeof(size_t));

        i += sizeof(size_t);

        const char* type = flowers[j].type.c_str();

        memmove(&buffer[i], type, strlen(type));

        i += strlen(type);
    }

    this->fifo.send(buffer, i);
}

void SellsNotification::send_close() {
    char close = CLOSE;

    this->fifo.send(&close, 1);
}

void SellsNotification::send_show_statistics() {
    char statistics = STATISTICS;

    this->fifo.send(&statistics, 1);
}

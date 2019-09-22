#include "statistics_notification.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>
#include <unistd.h>
#include <fcntl.h> 
#include <sstream>

#define FIFO "/tmp/statistics_fifo"
#define BYTES_RECEIVE 50

StatisticsNotification::StatisticsNotification() : fifo(FIFO) {

}

std::vector<FlowerBouquet> StatisticsNotification::retrieve_sells() {
    std::vector<FlowerBouquet> flowers;

    size_t total_flowers;
    std::string total_flow = this->receive();

    total_flowers = std::stoi(total_flow);

    for (int i = 0; i < (int) total_flowers; i++) {
        int productor_id;

        std::string productor = this->receive();

        productor_id = std::stoi(productor);

        std::string type = this->receive();

        flowers.push_back(FlowerBouquet(std::move(type), productor_id));
    }

    return std::move(flowers);
}

std::string StatisticsNotification::receive_message() {
    char type_msg;
    ssize_t bytes;
    std::string s;
    
    bytes = this->fifo.receive(&type_msg, 1);

    if (!bytes)
        throw; //Fifo closed

    s.push_back(type_msg);

    return std::move(s);
}

std::string StatisticsNotification::receive() {
    char char_size;
    std::string msg;

    this->fifo.receive(&char_size, 1);

    char buff[BYTES_RECEIVE + 1];

    std::string s;
    s.push_back(char_size);
    size_t size = std::stoi(s);

    while (size > BYTES_RECEIVE) {
        this->fifo.receive(&buff, BYTES_RECEIVE);
        msg.append(buff, BYTES_RECEIVE);
        size -= BYTES_RECEIVE;
    }

    this->fifo.receive(&buff, size);

    msg.append(buff, size);

    return std::move(msg);
}


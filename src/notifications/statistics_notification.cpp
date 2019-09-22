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

    this->fifo.receive(&total_flowers, sizeof(size_t));

    for (int i = 0; i < (int) total_flowers; i++) {
        int productor_id;

        this->fifo.receive(&productor_id, sizeof(int));

        std::string type;

        this->fifo.receive(type);

        flowers.push_back(FlowerBouquet(std::move(type), productor_id));
    }

    return std::move(flowers);
    /*std::vector<FlowerBouquet> flowers;

    size_t total_flowers;
    std::string total_flowers_str;
    
    this->fifo.receive(total_flowers_str);

    total_flowers = std::stoi(total_flowers_str);

    for (int i = 0; i < (int) total_flowers; i++) {
        int productor_id;

        std::string productor;

        this->fifo.receive(productor);

        productor_id = std::stoi(productor);

        std::string type;

        this->fifo.receive(type);

        flowers.push_back(FlowerBouquet(std::move(type), productor_id));
    }

    return std::move(flowers);*/
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

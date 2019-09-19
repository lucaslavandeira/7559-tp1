#include "sells_route.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>
#include <unistd.h>
#include <fcntl.h> 
#include <unordered_map>

#define FIFO "/tmp/statistics_fifo"

SellsRoute::SellsRoute(int mode) {
    const char* fifo = FIFO;

    //int ret = mkfifo(fifo, 0666);

    int ret = mknod(static_cast<const char*>(FIFO),S_IFIFO|0666,0);

    if (ret == -1) {
      //std::cout << "Fifo couldn't be created" << std::endl;
      //throw;
    }

    this->fd = open(fifo, mode);
  
    if (this->fd == -1) {
      std::cout << "Fifo couldn't be opened" << std::endl;
      throw;
    }
}

void SellsRoute::send_sells(std::vector<FlowerBouquet> flowers) {
    std::string total_flowers = std::to_string(flowers.size());

    this->send(total_flowers, total_flowers.size());

    for (int i = 0; i < (int) flowers.size(); i++) {
        std::string productor_id = std::to_string(flowers[i].productor_id);
        std::string type = flowers[i].type;

        this->send(productor_id, productor_id.size());
        this->send(type, type.size());
    }
}

std::vector<FlowerBouquet> SellsRoute::retrieve_sells() {
    std::vector<FlowerBouquet> flowers;

    std::string msg_total_flowers = this->receive();

    if (msg_total_flowers.compare("close") == 0)
        throw 1;

    int total_flowers = std::stoi(msg_total_flowers);

    for (int i = 0; i < total_flowers; i++) {
        std::string msg_productor_id = this->receive();

        if (msg_productor_id.compare("close") == 0)
            throw 1;

        int productor_id = std::stoi(msg_productor_id);

        std::string type = this->receive();

        if (type.compare("close") == 0)
            throw 1;        

        flowers.push_back(FlowerBouquet(std::move(type), productor_id));
    }
    
    return std::move(flowers);
}

void SellsRoute::send(const std::string &msg, size_t size) {
    write(this->fd, (const char *) &size, 1);
    write(this->fd, msg.c_str(), size);
}

std::string SellsRoute::receive() {
    char size;

    read(this->fd, &size, 1);

    char buff[BYTES_RECEIVE + 1];
    std::string s;

    while (size > BYTES_RECEIVE) {
        read(this->fd, &buff, BYTES_RECEIVE);
        s.append(buff, BYTES_RECEIVE);
        size -= BYTES_RECEIVE;
    }

    read(this->fd, &buff, size);
    s.append(buff, size);

    return s;
}

SellsRoute::~SellsRoute() {
    close(this->fd);
}

void SellsRoute::delete_route() {
    //unlink(FIFO);
}

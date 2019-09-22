#include "read_fifo.h"
#include "fifo.h"
#include <string>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>

#define BYTES_RECEIVE 50

ReadFifo::ReadFifo(std::string route) : Fifo(route, O_RDONLY) {
    
}

ssize_t ReadFifo::receive(void* buffer, size_t size) {
    ssize_t bytes = read(this->fd, buffer, size);
    return bytes;
}

ssize_t ReadFifo::receive(std::string& msg) {
    msg = "";
    size_t size;
    ssize_t bytes;

    bytes = this->receive(&size, sizeof(size_t));

    if (!bytes)
        return 0;

    char buff[BYTES_RECEIVE + 1];

    while (size > BYTES_RECEIVE) {
        bytes += this->receive(&buff, BYTES_RECEIVE);
        msg.append(buff, BYTES_RECEIVE);
        size -= BYTES_RECEIVE;
    }

    bytes += this->receive(&buff, size);

    msg.append(buff, size);

    return bytes;
}

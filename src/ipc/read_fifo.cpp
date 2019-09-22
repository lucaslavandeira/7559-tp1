#include "read_fifo.h"
#include "fifo.h"
#include <string>
#include <unistd.h>
#include <fcntl.h>

ReadFifo::ReadFifo(std::string route) : Fifo(route, O_RDONLY) {
    
}

ssize_t ReadFifo::receive(void* buffer, size_t size) {
    ssize_t bytes = read(this->fd, buffer, size);
    return bytes;
}

#include "write_fifo.h"
#include "fifo.h"
#include <string>
#include <unistd.h>
#include <fcntl.h>

WriteFifo::WriteFifo(std::string route) : Fifo(route, O_WRONLY) {
    
}

void WriteFifo::send(const void* buffer, size_t size) {
    write(this->fd, buffer, size);
}

#include "fifo.h"
#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>

Fifo::Fifo(std::string route, int mode) {
    if (mode != O_WRONLY && mode != O_RDONLY)
        throw;

    const char* fifo = route.c_str();

    mknod(static_cast<const char*>(fifo),S_IFIFO|0666,0);

    this->fd = open(fifo, mode);
  
    if (this->fd == -1) {
      std::cout << "Fifo couldn't be opened" << std::endl;
      throw;
    }
}

Fifo::~Fifo() {
    close(this->fd);
}

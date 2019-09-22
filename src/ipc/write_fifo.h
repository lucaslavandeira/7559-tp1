#ifndef WRITE_FIFO_H
#define WRITE_FIFO_H

#include "fifo.h"
#include <string>

class WriteFifo : public Fifo {
public:
    WriteFifo(std::string route);
    void send(const void* buffer, size_t size);
};

#endif

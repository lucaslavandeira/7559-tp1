#ifndef READ_FIFO_H
#define READ_FIFO_H

#include "fifo.h"
#include <string>

class ReadFifo : public Fifo {
public:
    ReadFifo(std::string route);
    ssize_t receive(void* buffer, size_t size);
    ssize_t receive(std::string& msg);
};

#endif

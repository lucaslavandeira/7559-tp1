#ifndef READ_FIFO_H
#define READ_FIFO_H

#include "fifo.h"
#include <string>

class ReadFifo : public Fifo {
public:
    ReadFifo(std::string route);
    /*
    Expects to receive size bytes into buffer
    Returns 0 if EOF detected
    */
    ssize_t receive(void* buffer, size_t size);
    /*
    Expects to receive a string into msg
    Returns 0 if EOF detected
    */
    ssize_t receive(std::string& msg);
};

#endif

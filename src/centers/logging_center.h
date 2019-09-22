#ifndef LOGGING_CENTER_H
#define LOGGING_CENTER_H

#include "../ipc/read_fifo.h"

class LoggingCenter {
private:
    ReadFifo fifo;
    bool debug_mode;
public:
    LoggingCenter(bool debug_mode);
    void work();
};

#endif

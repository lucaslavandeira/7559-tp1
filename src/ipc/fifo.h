#ifndef FIFO_H
#define FIFO_H

#include <string>

class Fifo {
protected:
    int fd;
    Fifo(std::string route, int mode);
    ~Fifo();
};

#endif

#ifndef FIFO_H
#define FIFO_H

#include <string>

class Fifo {
protected:
    int fd;
    /*
    Creates a fifo with mode O_RDONLY or O_WRONLY
    */
    Fifo(std::string route, int mode);
    ~Fifo();
};

#endif

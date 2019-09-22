#include "logging_center.h"
#include <fcntl.h>
#include <iostream>

#define FIFO "/tmp/logger_fifo"

LoggingCenter::LoggingCenter(bool debug_mode) : fifo(FIFO) {
    this->debug_mode = debug_mode;
}

void LoggingCenter::work() {
    ssize_t bytes;

    while (this->debug_mode) {
        std::string msg;

        bytes = this->fifo.receive(msg);

        if (!bytes) {
            std::cout << "Loggin center closed" << std::endl;
            break;
        }

        std::cout << "[LOG] " << msg << std::endl;
    }
}

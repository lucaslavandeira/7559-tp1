#ifndef LOGGING_CENTER_H
#define LOGGING_CENTER_H

#include "../ipc/read_fifo.h"

class LoggingCenter {
private:
    ReadFifo fifo;
    bool debug_mode;
    std::string path;

    std::string log_path() const;
    void save_log(std::string& log);
public:
    LoggingCenter(bool debug_mode);
    /*
    Logging center work loop
    */
    void work();
};

#endif

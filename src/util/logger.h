#ifndef LOGGER_H
#define LOGGER_H

#include "../ipc/write_fifo.h"
#include <string>
#include <sstream>

class Logger {
private:
    WriteFifo fifo;
    std::ostringstream ss;

public:
    Logger();
    Logger& operator<<(const std::string& msg);
    Logger& operator<<(int val);
    Logger& operator<<(std::ostream& (*os)(std::ostream&));
};

#endif

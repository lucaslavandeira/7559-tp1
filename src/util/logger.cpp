#include "logger.h"
#include <sstream>
#include <iostream>
#include "string.h"

#define FIFO "/tmp/logger_fifo"
#define MAX_BUFFER 1000

Logger::Logger() : fifo(FIFO) {

}

Logger& Logger::operator<<(const std::string& msg) {
    //this->fifo.send(msg.c_str(), msg.size());
    ss << msg;
    return *this;
}

Logger& Logger::operator<<(int val) {
    std::string msg = std::to_string(val);
    return *this << msg;
}

Logger& Logger::operator<<(std::ostream& (*os)(std::ostream&)) {
    this->ss << os;
    char buffer[MAX_BUFFER];
    size_t total_size = 0;

    std::string msg = this->ss.str();

    const char* msg_c = msg.c_str();

    size_t msg_size = msg.size();

    memcpy(buffer, &msg_size, sizeof(size_t));

    total_size += sizeof(size_t);

    memcpy(buffer +total_size, msg_c, strlen(msg_c));

    total_size += strlen(msg_c);

    this->fifo.send(buffer, total_size);
    return *this;
}

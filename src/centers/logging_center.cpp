#include "logging_center.h"
#include <fcntl.h>
#include <iostream>
#include "../util/home_dir.h"
#include "../util/create_directory_if_not_exists.h"
#include "../config.h"
#include <sstream>
#include <fstream>

#define FIFO "/tmp/logger_fifo"
#define PATH "log"

LoggingCenter::LoggingCenter(bool debug_mode) : fifo(FIFO) {
    this->debug_mode = debug_mode;
    this->path = log_path();
}

void LoggingCenter::work() {
    ssize_t bytes;

    while (this->debug_mode) {
        std::string msg;

        bytes = this->fifo.receive(msg);

        if (!bytes) {
            break;
        }

        this->save_log(msg);
    }
}

void LoggingCenter::save_log(std::string& log) {
    std::basic_string<char> path = this->path;

    std::ofstream f(path, std::ios_base::app);

    if (!f.good()) {
        return;
    }

    f << log;
}

std::string LoggingCenter::log_path() const {
    const char* home = home_dir();
    std::stringstream stream;

    stream << home << "/" << CONFIG_PATH << "/";
    create_directory_if_not_exists(stream.str());
    stream << PATH << "/";
    create_directory_if_not_exists(stream.str());
    stream << PATH;

    return stream.str();
}
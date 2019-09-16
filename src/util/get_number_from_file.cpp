#include <sys/stat.h>
#include <fstream>
#include <iostream>
#include "get_number_from_file.h"

int get_number_from_file(const std::string& path) {
    struct stat buffer = {0};
    if (stat(path.c_str(), &buffer) < 0) {
        // No existe el archivo / error
        return 0;
    }

    std::ifstream stream(path);
    std::string number;
    stream >> number;

    return std::atoi(number.c_str());
}

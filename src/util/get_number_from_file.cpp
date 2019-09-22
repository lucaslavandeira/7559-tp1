#include <sys/stat.h>
#include <fstream>
#include <iostream>
#include "get_number_from_file.h"
#include <vector>
#include "../flower_bouquet.h"
#include <sstream>
#include <unordered_map>
#include <queue>

int get_number_from_file(const std::string& path) {
    struct stat buffer = {0};
    if (stat(path.c_str(), &buffer) < 0) {
        // No existe el archivo / error
        return 0;
    }

    std::ifstream stream(path);
    std::string number;
    stream >> number;
    stream.close();
    return std::atoi(number.c_str());
}

std::unordered_map<std::string, std::queue<FlowerBouquet>> get_flowers_from_file(const std::string& path) {
    struct stat buffer = {0};
    std::unordered_map<std::string, std::queue<FlowerBouquet>> flowers{};

    if (stat(path.c_str(), &buffer) < 0) {
        // No existe el archivo / error
        return flowers;
    }

    std::ifstream stream(path);

    std::string line;

    while (std::getline(stream, line)) {
        std::istringstream iss(line);
        std::string type;
        int productor_id;

        if (!(iss >> type >> productor_id)) { break; } // error

        flowers[type].push(FlowerBouquet(type, productor_id));
    }

    return std::move(flowers);
}

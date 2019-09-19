#ifndef TP1_GET_NUMBER_FROM_FILE_H
#define TP1_GET_NUMBER_FROM_FILE_H


#include <string>
#include "../flower_bouquet.h"
#include <unordered_map>
#include <vector>

int get_number_from_file(const std::string& path);
std::unordered_map<std::string, std::vector<FlowerBouquet>> get_flowers_from_file(const std::string& path);

#endif //TP1_GET_NUMBER_FROM_FILE_H

#include "statistics_center.h"
#include "../ipc/sells_route.h"
#include <iostream>
#include <fcntl.h> 
#include <zconf.h>
#include <sys/stat.h>

StatisticsCenter::StatisticsCenter() : sells_route(O_RDONLY) {

}

void StatisticsCenter::work() {
    while (true) {
        std::vector<FlowerBouquet> sells;

        try {            
            sells = this->sells_route.retrieve_sells();
            this->update_statistics(sells);
        } catch (int e) {
            break;
        }
    }

    //this->sells_route.delete_route();
}

void StatisticsCenter::update_statistics(std::vector<FlowerBouquet> sells) {
    for (int i = 0; i < (int) sells.size(); i++) {
        if (!productors_statistics.count(sells[i].productor_id))
            productors_statistics[sells[i].productor_id] = 0;

        if (!flowers_statistics.count(sells[i].type))
            flowers_statistics[sells[i].type] = 0;  

        productors_statistics[sells[i].productor_id]++;
        flowers_statistics[sells[i].type]++;
    }

    update_best_productor();
    update_best_selling_flower();
}

void StatisticsCenter::update_best_productor() {
    int best_productor;
    int sells_ammount = -1;

    for (auto& it : productors_statistics) {
        if (it.second > sells_ammount) {
            best_productor = it.first;
            sells_ammount = it.second;
        }
    }

    std::cout << "El productor más vendido es: " << best_productor << std::endl;
}

void StatisticsCenter::update_best_selling_flower() {
    std::string best_flower;
    int sells_ammount = -1;

    for (auto& it : flowers_statistics) {
        if (it.second > sells_ammount) {
            best_flower = it.first;
            sells_ammount = it.second;
        }
    }

    std::cout << "La flor más vendida fue: " << best_flower << std::endl;
}

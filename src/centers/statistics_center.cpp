#include "statistics_center.h"
#include "../notifications/statistics_notification.h"
#include <iostream>
#include <fcntl.h> 
#include <zconf.h>
#include <sys/stat.h>

#define STATISTICS_MSG "s"
#define EXIT_MSG "c"

StatisticsCenter::StatisticsCenter() {
    this->best_flower = "Ninguna flor fue vendida";
    this->best_productor = "Ningun productor vendio flores";
}

void StatisticsCenter::work() {
    while (true) {
        std::vector<FlowerBouquet> sells;

        try {
            std::string msg = this->sells_route.receive_message();

            if (msg.compare(STATISTICS_MSG) == 0) {
                this->show_statistics();
                continue;
            } else if (msg.compare(EXIT_MSG) == 0) {
                break;
            }

            sells = this->sells_route.retrieve_sells();
            this->update_statistics(sells);
        } catch (int e) {
            break;
        }
    }
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
    int best_productor = -1;
    int sells_ammount = -1;

    for (auto& it : productors_statistics) {
        if (it.second > sells_ammount) {
            best_productor = it.first;
            sells_ammount = it.second;
        }
    }

    if (best_productor == -1) {
        this->best_productor = "Ningun productor vendio flores";
        return;
    }

    this->best_productor = std::to_string(best_productor);
}

void StatisticsCenter::update_best_selling_flower() {
    std::string best_flower = "";
    int sells_ammount = -1;

    for (auto& it : flowers_statistics) {
        if (it.second > sells_ammount) {
            best_flower = it.first;
            sells_ammount = it.second;
        }
    }

    if (best_flower.compare("") == 0) {
        this->best_flower = "Ninguna flor fue vendida";
        return;
    }

    this->best_flower = best_flower;
}

void StatisticsCenter::show_statistics() {
    std::cout << "Productor que mas vendio: " << this->best_productor << std::endl
                << "Flor mas vendida: " << this->best_flower << std::endl;
}

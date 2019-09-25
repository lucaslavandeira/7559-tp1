#ifndef STATISTICS_CENTER_H
#define STATISTICS_CENTER_H

#include "../notifications/statistics_notification.h"
#include <vector>
#include "../flower_bouquet.h"
#include <unordered_map>

class StatisticsCenter {
private:
    static const std::string no_flower_msg;
    static const std::string no_productor_msg;

    std::unordered_map<int, int> productors_statistics;
    std::unordered_map<std::string, int> flowers_statistics;
    std::string best_flower;
    std::string best_productor;

    StatisticsNotification sells_route;
    /*
    Update actual statistics based on new sells
    */
    void update_statistics(std::vector<FlowerBouquet> sells);
    /*
    Updates the new best productor based on new sells
    */    
    void update_best_productor();
    /*
    Updates the new best selling flower based on new sells
    */
    void update_best_selling_flower();
    /*
    Prints the best productor and best selling flower
    */    
    void show_statistics();
    /*
    Saves statistics for future use
    */    
    void save_statistics();
    /*
    Saves the information of sells made by each productor
    */   
    void save_best_productor();
    /*
    Saves the information of the sold flowers
    */    
    void save_best_flower();
    /*
    Loads the information of sells made by each productor
    */    
    void load_best_productor();
    /*
    Loads the information of the sold flowers
    */
    void load_best_flower();
    /*
    Get the path of a file from statistics named "name"
    */   
    std::string statistics_path(const char* name) const;
public:
    StatisticsCenter();
    void work();
};

#endif

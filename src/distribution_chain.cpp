#include <unistd.h>
#include <sys/wait.h> 
#include <iostream>
#include <cstring>
#include "distribution_chain.h"
#include "production_center.h"
#include "distribution_center.h"
#include "sells_center.h"
#include "route.h"

int DistributionChain::create() {
    DistributionCenter distribution_center;
    ProductionCenter production_center;
    SellsCenter sells_center;

    Route production_route;
    Route distribution_route;

    production_center.associate_route(production_route);
    distribution_center.associate_receive_route(production_route);
    distribution_center.associate_send_route(distribution_route);
    sells_center.associate_route(distribution_route);

    int pid = fork();

    if (pid != 0) {
        production_center.work();
        return pid;
    }

    pid = fork();

    if (pid != 0) {
        distribution_center.work();
        return pid;
    } 
    
    sells_center.work();

    //Se podria hacer otro fork y el proceso "main", es decir, la cadena de distribucion,
    //podría esperar a cada hijo para ver que devuelven (?)

    return pid;         
}

void DistributionChain::interrupt_operations() {

}

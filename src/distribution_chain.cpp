#include <unistd.h>
#include <sys/wait.h> 
#include <iostream>
#include "distribution_chain.h"
#include "centers/production_center.h"
#include "centers/distribution_center.h"
#include "centers/sells_center.h"
#include "routes/production_route.h"
#include "routes/distribution_route.h"

DistributionChain::DistributionChain(int chain_id) : chain_id(chain_id) {}

int DistributionChain::start() {
    DistributionCenter distribution_center;
    ProductionCenter production_center;
    SellsCenter sells_center;

    ProductionRoute production_route;
    DistributionRoute distribution_route;

    production_center.associate_route(production_route);
    distribution_center.associate_receive_route(production_route);
    distribution_center.associate_send_route(distribution_route);
    sells_center.associate_route(distribution_route);

    int pid = fork();

    if (pid != 0) {
        production_center.work();
        waitpid(pid, nullptr, 0);
        return pid;
    }

    pid = fork();

    if (pid != 0) {
        distribution_center.work();
        waitpid(pid, nullptr, 0);
        return pid;
    }
    
    sells_center.work();

    //Se podria hacer otro fork y el proceso "main", es decir, la cadena de distribucion,
    //podría esperar a cada hijo para ver que devuelven (?)

    return pid;         
}

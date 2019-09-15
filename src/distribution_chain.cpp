#include <unistd.h>
#include <sys/wait.h> 
#include <iostream>
#include "distribution_chain.h"
#include "production_center.h"
#include "distribution_center.h"
#include "sells_center.h"
#include "production_route.h"
#include "distribution_route.h"

int DistributionChain::create() {
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
        std::cout << "LLego acá?" << std::endl;
        return pid;
    }
    
    sells_center.work();

    //Se podria hacer otro fork y el proceso "main", es decir, la cadena de distribucion,
    //podría esperar a cada hijo para ver que devuelven (?)

    return pid;         
}

void DistributionChain::interrupt_operations() {

}

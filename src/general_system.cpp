#include "general_system.h"
#include "distribution_chain.h"
#include <vector>
#include <zconf.h>
#include <cstdlib>

GeneralSystem::GeneralSystem() {

}

int GeneralSystem::create_distribution_chain() {

    DistributionChain chain;
    int pid = fork();
    if (pid != 0) { // Parent
        struct chain_process process;
        process.chain = chain;
        process.pid = pid;
        this->chains.push_back(process);
        return pid;
    }

    // Forks multiple times, all infinite loops until exit command
    chain.create();
    std::exit(0);
    return 0;
}

void GeneralSystem::interrupt_operations() {
}

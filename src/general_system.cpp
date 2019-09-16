#include "general_system.h"
#include "distribution_chain.h"
#include <vector>
#include <zconf.h>
#include <cstdlib>
#include <wait.h>

GeneralSystem::GeneralSystem(int workers_count) :
    workers_count(workers_count),
    flag(false) {
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

void GeneralSystem::init() {
    for (int i = 0; i < workers_count; ++i) {
        struct chain_process c;
        create_distribution_chain();
    }
}

void GeneralSystem::finish() {
    flag.exit();
    for (auto chain: chains) {
        waitpid(chain.pid, nullptr, 0);
    }
}

#include "general_system.h"
#include "distribution_chain.h"
#include <zconf.h>
#include <cstdlib>
#include <wait.h>

GeneralSystem::GeneralSystem(int workers_count) :
    workers_count(workers_count),
    flag(false) {
}

int GeneralSystem::create_distribution_chain(int chain_id) {

    DistributionChain chain(chain_id);
    int pid = fork();
    if (pid != 0) { // Parent
        this->chain_pids.push_back(pid);
        return pid;
    }

    // Forks multiple times, all infinite loops until exit command
    chain.start();
    std::exit(0);
    return 0;
}

void GeneralSystem::init() {
    for (int i = 0; i < workers_count; ++i) {
        create_distribution_chain(i);
    }
}

void GeneralSystem::finish() {
    flag.exit();
    for (auto pid: chain_pids) {
        waitpid(pid, nullptr, 0);
    }
}

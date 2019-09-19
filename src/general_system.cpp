#include "general_system.h"
#include "distribution_chain.h"
#include <zconf.h>
#include <cstdlib>
#include <wait.h>
#include "centers/statistics_center.h"
#include <iostream>

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
    //std::exit(0);
    return 0;
}

int GeneralSystem::create_statistics_center() {
    int pid = fork();

    if (pid != 0) {
        this->chain_pids.push_back(pid);
        return pid;
    }

    StatisticsCenter center;
    center.work();

    return 0;
}

int GeneralSystem::init() {
    std::vector<int> chain_ids;

    for (int i = 0; i < workers_count; ++i) {
        int pid = create_distribution_chain(i);
        if (pid == 0) {
            return 0;
        }

        chain_ids.push_back(i);
    }

    return create_statistics_center();
}

void GeneralSystem::finish() {
    flag.exit();
    for (auto pid: chain_pids) {
        waitpid(pid, nullptr, 0);
    }
}

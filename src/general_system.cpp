#include "general_system.h"
#include "distribution_chain.h"
#include <zconf.h>
#include <cstdlib>
#include <wait.h>
#include "centers/statistics_center.h"
#include "centers/logging_center.h"
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

int GeneralSystem::create_logging_center(bool debug_mode) {
    int pid = fork();

    if (pid != 0) {
        this->chain_pids.push_back(pid);
        return pid;
    }

    LoggingCenter center(debug_mode);
    center.work();

    return 0;
}

int GeneralSystem::init(bool debug_mode) {
    std::vector<int> chain_ids;
    int pid;

    for (int i = 0; i < workers_count; ++i) {
        pid = create_distribution_chain(i);

        if (pid == 0)
            return 0;

        chain_ids.push_back(i);
    }

    pid = create_statistics_center();

    if (pid == 0)
        return 0;
    
    return create_logging_center(debug_mode);
}

void GeneralSystem::finish() {
    flag.exit();
    for (auto pid: chain_pids) {
        waitpid(pid, nullptr, 0);
    }
}

#ifndef GENERAL_SYSTEM_H
#define GENERAL_SYSTEM_H

#include <vector>
#include "distribution_chain.h"
#include "ipc/ExitFlag.h"

class GeneralSystem {
private:
    std::vector<int> chain_pids;
    int workers_count;
    ExitFlag flag;
    /*
    Creates a distribution chain that creates 3 processes:
    A production center
    A distribution center
    A sells center

    returns PID
    */
    int create_distribution_chain(int chain_id);
    /*
    Creates a process to read statistics and print them out
    returns PID
    */    
    int create_statistics_center();
    /*
    Creates a process to flush logs into a file
    returns PID
    */
    int create_logging_center(bool debug_mode);
public:
    explicit GeneralSystem(int workers_count);
    /*
    Creates the distribution chain, statistics center and logging center
    returns PID
    */
    int init(bool debug_mode);
    /*
    Stop all the processes
    */    
    void finish();
};

#endif

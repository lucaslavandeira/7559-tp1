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

    int create_distribution_chain(int chain_id);
    int create_statistics_center();
public:
  explicit GeneralSystem(int workers_count);
  int init();
  void finish();
};

#endif

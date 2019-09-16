#ifndef GENERAL_SYSTEM_H
#define GENERAL_SYSTEM_H

#include <vector>
#include "distribution_chain.h"
#include "ipc/ExitFlag.h"

struct chain_process {
    int pid;
    DistributionChain chain;
};

class GeneralSystem {
    int workers_count;
    ExitFlag flag;
public:
  std::vector<chain_process> chains;

  explicit GeneralSystem(int workers_count);
  int create_distribution_chain();
  void init();
  void finish();
};

#endif

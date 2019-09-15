#ifndef GENERAL_SYSTEM_H
#define GENERAL_SYSTEM_H

#include <vector>
#include "distribution_chain.h"

struct chain_process {
    int pid;
    DistributionChain chain;
};

class GeneralSystem {
public:
  std::vector<chain_process> chains;

  GeneralSystem();
  int create_distribution_chain();
  void interrupt_operations();
};

#endif

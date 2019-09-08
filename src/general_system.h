#ifndef GENERAL_SYSTEM_H
#define GENERAL_SYSTEM_H

#include <vector>
#include "distribution_chain.h"

class GeneralSystem {
public:
  std::vector<DistributionChain> chains;

  GeneralSystem();
  void add_distribution_chain(DistributionChain& chain);
  void interrupt_operations();
};

#endif

#ifndef GENERAL_SYSTEM_H
#define GENERAL_SYSTEM_H

#include <vector>
#include "distribution_chain.h"
#include "ipc/ExitFlag.h"

class GeneralSystem {
    int workers_count;
    ExitFlag flag;
public:
  std::vector<int> chain_pids;

  explicit GeneralSystem(int workers_count);
  int create_distribution_chain(int chain_id);
  void init();
  void finish();
};

#endif

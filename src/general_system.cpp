#include "general_system.h"
#include "distribution_chain.h"
#include <vector>

GeneralSystem::GeneralSystem() {

}

void GeneralSystem::add_distribution_chain(DistributionChain& chain) {
  this->chains.push_back(chain);
}

void GeneralSystem::interrupt_operations() {
  for (int i = 0; i < (int) this->chains.size(); i++) {
    this->chains[i].interrupt_operations();
  }
}

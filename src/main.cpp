#include <iostream>
#include "production_center.h"

int main(int argc, char* argv[]) {
  ProductionCenter center;
  std::cout << "Harvesting " << center.harvest() << " bouquets: " << std::endl;

  return 0;
}

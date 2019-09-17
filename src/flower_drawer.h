#ifndef FLOWER_DRAWER_H
#define FLOWER_DRAWER_H

#include "flower_bouquet.h"
#include <vector>

#define DRAWER_CAPACITY 10


class FlowerDrawer {
public:
  std::vector<FlowerBouquet> flowers;
  int productor_id;

  FlowerDrawer(std::vector<FlowerBouquet> flowers, int productor_id);
};

#endif

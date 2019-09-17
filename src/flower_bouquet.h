#ifndef FLOWER_BOUQUET_H
#define FLOWER_BOUQUET_H

#include <string>

class FlowerBouquet {
public:
  std::string type;
  int productor_id;

  FlowerBouquet(std::string type, int productor_id);
};

#endif

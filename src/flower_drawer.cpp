#include "flower_drawer.h"

#include "flower_bouquet.h"
#include <vector>

FlowerDrawer::FlowerDrawer(std::vector<FlowerBouquet> flowers, int productor_id) {
  if (flowers.size() > DRAWER_CAPACITY) {
    //Throw exception?
  }

  this->flowers = flowers;
  this->productor_id = productor_id;
}

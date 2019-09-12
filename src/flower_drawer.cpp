#include "flower_drawer.h"

FlowerDrawer::FlowerDrawer(int rose_bouquets, int tulip_bouquets) {
  if (rose_bouquets + tulip_bouquets > DRAWER_CAPACITY) {
    //Throw exception?
  }

  this->rose_bouquets = rose_bouquets;
  this->tulip_bouquets = tulip_bouquets;
}

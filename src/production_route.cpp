#include "production_route.h"
#include "route.h"
#include "flower_drawer.h"
#include <string>

ProductionRoute::ProductionRoute() {

}

void ProductionRoute::send(FlowerDrawer& drawer) {
  std::string roses = std::to_string(drawer.rose_bouquets);
  std::string tulips = std::to_string(drawer.tulip_bouquets);

  this->route.send(roses, roses.size());
  this->route.send(tulips, tulips.size());
}

FlowerDrawer ProductionRoute::receive() {
  std::string roses = this->route.receive();
  std::string tulips = this->route.receive();

  return FlowerDrawer(std::stoi(roses), std::stoi(tulips));
}

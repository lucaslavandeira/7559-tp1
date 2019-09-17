#include "production_route.h"
#include "route.h"
#include "../flower_drawer.h"
#include <string>
#include <iostream>
#include "../flower_bouquet.h"
#include <vector>

const std::string ProductionRoute::send_msg = "Drawer sent";
const std::string ProductionRoute::close_msg = "Close";

ProductionRoute::ProductionRoute() : route(close_msg) {

}

void ProductionRoute::send(FlowerDrawer& drawer) {
  std::vector<FlowerBouquet> flowers = drawer.flowers;

  this->route.send(this->send_msg, this->send_msg.size());

  std::string productor = std::to_string(drawer.productor_id);

  this->route.send(productor, productor.size());

  std::string total_flowers = std::to_string(flowers.size());

  this->route.send(total_flowers, total_flowers.size());

  for (int i = 0; i < (int) flowers.size(); i++) {
    this->route.send(flowers[i].type, flowers[i].type.size());
  }
}

FlowerDrawer ProductionRoute::receive() {
  std::vector<FlowerBouquet> flowers;

  std::string msg = this->route.receive();

  if (msg.compare(close_msg) == 0) {
    throw 1;
  }

  int productor_id = std::stoi(this->route.receive());
  int total_flowers = std::stoi(this->route.receive());

  for (int i = 0; i < total_flowers; i++) {
    std::string type = this->route.receive();

    flowers.push_back(FlowerBouquet(type, productor_id));
  }

  return FlowerDrawer(std::move(flowers), productor_id); 
}

void ProductionRoute::close() {
    this->route.send(close_msg, close_msg.size());
}

#include "route.h"
#include <unistd.h>
#include <iostream>
#include <cstring>
#include <fcntl.h>

Route::Route() {
  create_route(this->pipefds);
}

void Route::create_route(int pipefds[2]) {
  if (pipe(pipefds) != 0) {
      std::cout << "Error en pipe" << std::strerror(errno) << std::endl;
      throw; // Manejar errores!!!???
  }  
}

void Route::send(int bouquets) {
  //std::string msg = std::to_string(bouquets);
  //write(pipefds[1], msg.c_str(), msg.size());  
  write(this->pipefds[1], &bouquets, sizeof(int));
}

int Route::receive() {
  char data[sizeof(int)];
  read(this->pipefds[0], data, 4);
  //return std::atoi(data);
  int value = (int) data[0];

  return value;
}

Route::~Route() {
  close(this->pipefds[0]);
  close(this->pipefds[1]);
}
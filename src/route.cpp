#include "route.h"
#include <unistd.h>
#include <iostream>
#include <cstring>
#include <fcntl.h>


#define CLOSE_MSG "close"

Route::Route() {
  create_route(this->pipefds);
}

void Route::create_route(int pipefds[2]) {
  if (pipe(pipefds) != 0) {
      std::cout << "Error en pipe" << std::strerror(errno) << std::endl;
      throw; // Manejar errores!!!???
  }  
}

void Route::send(std::string msg, size_t size) {
  write(pipefds[1], (const char*) &size, 1);
  write(pipefds[1], msg.c_str(), size);
}

std::string Route::receive() {
  char size;

  read(pipefds[0], &size, 1);

  char buff[BYTES_RECEIVE+1];
  std::string s;

  while (size > BYTES_RECEIVE) {
    read(pipefds[0], &buff, BYTES_RECEIVE);
    s.append(buff, BYTES_RECEIVE);
    size -= BYTES_RECEIVE;
  }

  read(pipefds[0], &buff, size);
  s.append(buff, size); 

  return std::move(s);
}

Route::~Route() {
  ::close(this->pipefds[0]);
  ::close(this->pipefds[1]);
}

void Route::close() {
    send(CLOSE_MSG, strlen(CLOSE_MSG));
}

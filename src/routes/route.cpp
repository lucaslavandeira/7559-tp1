#include "route.h"
#include <unistd.h>
#include <iostream>
#include <cstring>


#define CLOSE_MSG "close"

Route::Route() {
    pipefds[0] = {0};
    pipefds[1] = {0};
    create_route();
}

void Route::create_route() {
    if (pipe(pipefds) != 0) {
        std::cout << "Error en pipe" << std::strerror(errno) << std::endl;
        throw; // Manejar errores!!!???
    }
}

void Route::send(const std::string &msg, size_t size) {
    write(pipefds[1], (const char *) &size, 1);
    write(pipefds[1], msg.c_str(), size);
}

std::string Route::receive() {
    char size;

    read(pipefds[0], &size, 1);

    char buff[BYTES_RECEIVE + 1];
    std::string s;

    while (size > BYTES_RECEIVE) {
        read(pipefds[0], &buff, BYTES_RECEIVE);
        s.append(buff, BYTES_RECEIVE);
        size -= BYTES_RECEIVE;
    }

    read(pipefds[0], &buff, size);
    s.append(buff, size);

    return s;
}

Route::~Route() {
    ::close(this->pipefds[0]);
    ::close(this->pipefds[1]);
}

void Route::close() {
    send(CLOSE_MSG, strlen(CLOSE_MSG));
}

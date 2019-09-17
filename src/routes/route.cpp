#include "route.h"
#include <unistd.h>
#include <iostream>
#include <cstring>

Route::Route(std::string eof_msg) {
    this->eof_msg = eof_msg;
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

    int bytes = read(pipefds[0], &size, 1);

    if (!bytes)
        return this->eof_msg;

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

#include <sys/ipc.h>
#include <sys/shm.h>
#include <cstdio>
#include <iostream>
#include "ExitFlag.h"


static key_t init_token() {
    key_t tok = ftok("./src/main.cpp", time(NULL));
    if (tok == -1) {
        perror("ftok");
        throw;
    }
    return tok;
}

const static key_t token = init_token();

ExitFlag::~ExitFlag() {
    if (flag) {
        shmdt(flag);
        shmctl(this->shared_memory_id, IPC_RMID, nullptr);
    }
}

ExitFlag::ExitFlag(const bool readonly) {
    int flags = 0600;
    if (!readonly) {
        flags |= IPC_CREAT | IPC_EXCL;
    }
    if (readonly) {
        flags |= SHM_RDONLY;
    }
    this->shared_memory_id = shmget(token, sizeof(bool), flags);
    if (shared_memory_id < 0) {
        perror("shmget");
    }

    int shmat_flags = 0;
    if (readonly) {
        shmat_flags |= SHM_RDONLY;
    }
    void* address = shmat(this->shared_memory_id, nullptr, shmat_flags);
    if (address == (void*) -1) {
        perror("Error creando memoria compartida");
    }
    this->flag = (bool*) address;
    if (!readonly) {
        *this->flag = true;
    }

}

bool ExitFlag::read() {
    return *this->flag;
}

ExitFlag::ExitFlag(): ExitFlag(true) {
}

void ExitFlag::exit() {
    *this->flag = false;
}

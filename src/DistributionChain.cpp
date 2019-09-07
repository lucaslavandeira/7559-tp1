#include <unistd.h>
#include <iostream>
#include <cstring>
#include "DistributionChain.h"
#include "production_center.h"

int DistributionChain::create() {
    int pid;
    int pipefds[2];

    pid = fork();
    if (pid != 0) {
        std::cout << "Cierro main!!" << std::endl;
        return pid;  // return a main
    }

    // Soy el production center
    init_pipe(pipefds);

    pid = fork();

    if (pid != 0) {
        // Soy el production center, le mando cosas forever a mi hijo (distribution center)
        // Utilizo pipefds[1] para ESCRIBIR
        while(true) {
            int harvest = ProductionCenter().harvest();
            std::string msg = std::to_string(harvest);
            write(pipefds[1], msg.c_str(), msg.size());
            break;
        }
        std::cout << "Cierro el production center!!" << std::endl;
        return pid;
    }

    // Soy el distribution center
    int production_center_fd = pipefds[0];
    init_pipe(pipefds);
    pid = fork();
    if (pid != 0) {
        while(true) {
            // Soy el distribution center
            // LEO del pipe de production center, y ENVÍO hacia el pipe de punto de venta
            char data[4];
            read(production_center_fd, data, 4);
            int flowers = std::atoi(data);
            // Procesamiento del distribution center goes here
            std::string msg = std::to_string(flowers);
            write(pipefds[1], msg.c_str(), msg.size());
            break;
        }
        std::cout << "Cierro el distribution center!" << std::endl;
        return pid;
    }

    // Soy el punto de venta
    int distribution_center_fd = pipefds[0];
    char data[4];
    read(distribution_center_fd, data, 4);
    std::cout << "Hola del punto de venta! Recibí " << data << " desde el centro!!!" << std::endl;
    return 0;
}

void DistributionChain::init_pipe(int* pipefds) {
    if (pipe(pipefds) != 0) {
        std::cout << "Error en pipe" << std::strerror(errno) << std::endl;
        throw; // Manejar errores!!!???
    }
}

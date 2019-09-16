#include <iostream>
#include <wait.h>
#include "centers/production_center.h"
#include "general_system.h"
#include "ipc/ExitFlag.h"

#define INTERRUPT_CMD "q"

std::vector<int> init(GeneralSystem &system);

void read_exit_command();

int main(int argc, char *argv[]) {
    GeneralSystem system;
    ExitFlag flag(false);

    //TODO: reemplazar por argv
    std::vector<int> ids = init(system);

    read_exit_command();
    std::cout << "Saliendo..." << std::endl;
    flag.exit();

    for (int pid : ids) {
        waitpid(pid, nullptr, 0);
    }
    return 0;
}

void read_exit_command() {
    std::string input;

    while (true) {
        std::cin >> input;

        if (input == INTERRUPT_CMD) {
            return;
        }

    }
}

std::vector<int> init(GeneralSystem &system) {
    std::vector<int> pids;
    pids.reserve(1);
    for (int i = 0; i < 1; i++) {
        pids.push_back(system.create_distribution_chain());
    }
    return pids;
}

#include <iostream>
#include <wait.h>
#include <getopt.h>
#include "centers/production_center.h"
#include "general_system.h"
#include "ipc/ExitFlag.h"

#define INTERRUPT_CMD "q"

std::vector<int> init(GeneralSystem &system, int count);

void read_exit_command();

int get_workers(int argc, char **argv);

int main(int argc, char *argv[]) {
    GeneralSystem system;
    ExitFlag flag(false);

    int workers_count = get_workers(argc, argv);
    std::vector<int> ids = init(system, workers_count);

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

std::vector<int> init(GeneralSystem &system, int count) {
    std::vector<int> pids;
    pids.reserve(count);
    for (int i = 0; i < count; i++) {
        pids.push_back(system.create_distribution_chain());
    }
    return pids;
}

int get_workers(int argc, char **argv) {
    int opt = getopt(argc, argv, "c:");
    switch(opt) {
        case 'c':
            return std::atoi(optarg);
        default:
            return 1;
    }
}

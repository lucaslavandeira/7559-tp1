#include <iostream>
#include <getopt.h>
#include "general_system.h"
#include "util/get_number_from_file.h"

#define INTERRUPT_CMD "q"

std::vector<int> init(GeneralSystem &system, int count);

void read_exit_command();

int get_workers(int argc, char **argv);

int main(int argc, char *argv[]) {
    int workers_count = get_workers(argc, argv);
    GeneralSystem system(workers_count);
    system.init();

    read_exit_command();
    std::cout << "Saliendo..." << std::endl;
    system.finish();
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

int get_workers(int argc, char **argv) {
    int opt = getopt(argc, argv, "c:");
    switch(opt) {
        case 'c':
            return std::atoi(optarg);
        default:
            return 1;
    }
}

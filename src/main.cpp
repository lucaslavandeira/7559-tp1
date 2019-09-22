#include <iostream>
#include <getopt.h>
#include "general_system.h"
#include "util/get_number_from_file.h"
#include <fcntl.h>
#include "ipc/sells_route.h"
#include "orders/internet_orders.h"

#define INTERRUPT_CMD "q"

std::vector<int> init(GeneralSystem &system, int count);

void read_exit_command();

int get_workers(int argc, char **argv);

int simulation(int argc, char *argv[]) {
    int workers_count = get_workers(argc, argv);
    GeneralSystem system(workers_count);
    int pid = system.init();

    if (pid == 0)
        return 0;

    read_exit_command();
    std::cout << "Saliendo..." << std::endl;
    system.finish();
    return 0;
}

int main(int argc, char* argv[]) {
    return simulation(argc, argv);
}

void read_exit_command() {
    std::string input;

    while (true) {
        std::cin >> input;

        if (input == INTERRUPT_CMD) {
            SellsRoute sells_route(O_WRONLY);

            std::string msg = "close";
            sells_route.send(msg, msg.size());
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

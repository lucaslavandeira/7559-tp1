#include <iostream>
#include <getopt.h>
#include "general_system.h"
#include "util/get_number_from_file.h"
#include <fcntl.h>
#include "notifications/sells_notification.h"
#include "orders/internet_orders.h"

#define INTERRUPT_CMD "q"
#define STATISTICS_CMD "s"

std::vector<int> init(GeneralSystem &system, int count);

void read_exit_command();

int get_workers(int argc, char **argv);

int simulation(int argc, char *argv[]) {
    bool debug_mode = true;

    int workers_count = get_workers(argc, argv);

    GeneralSystem system(workers_count);

    int pid = system.init(debug_mode);

    if (pid == 0)
        return 0;

    read_exit_command();
    system.finish();
    return 0;
}

int main(int argc, char* argv[]) {
    return simulation(argc, argv);
}

void read_exit_command() {
    std::string input;
    SellsNotification sells_route;
    while (true) {
        std::cin >> input;

        if (input == INTERRUPT_CMD) {
            sells_route.send_close();
            return;
        } else if (input == STATISTICS_CMD) {
            sells_route.send_show_statistics();
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

#include <iostream>
#include <zconf.h>
#include <sys/wait.h> 
#include "production_center.h"
#include "distribution_chain.h"
#include "general_system.h"

#define INTERRUPT_CMD "q"

bool init(GeneralSystem &system);

int main(int argc, char* argv[]) {
    GeneralSystem system;

    //TODO: reemplazar por argv
    bool parent = init(system);

    if (parent) {
      bool wait_quit = true;
      std::string input;

      while (wait_quit) {
        std::cin >> input;

        if (!input.compare(INTERRUPT_CMD)) {
          wait_quit = false;
          system.interrupt_operations();
        }
      }
    }

    //wait(NULL);

    //Se podria hacer que el padre espere a todos los hijos si es necesario

    if (parent)
      std::cout << "Main termino exitosamente!!" << std::endl;

    return 0;
}

bool init(GeneralSystem &system) {
    bool father = true;
    for (int i = 0; i < 1; i++) {
      //TODO: agregar en chain "algo" similar a una Route para propagar el exit
      DistributionChain chain;
      int pid = fork();

      if (pid != 0) {
        system.add_distribution_chain(chain);
      }
      else {
        chain.create();
        father = false;
        break;
      }
    }
    return father;
}

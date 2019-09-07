#include <iostream>
#include <zconf.h>
#include "production_center.h"
#include "DistributionChain.h"

int main(int argc, char* argv[]) {
    DistributionChain d;
    d.create();
    sleep(1);  // demosle tiempo a los forks a correr y hacer prints antes de salir
    // Handler de salida limpia desde el main goes here
    return 0;
}

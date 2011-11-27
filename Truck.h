#ifndef TRUCK_
#define TRUCK_

#include <uC++.h>

#include "NameServer.h"
#include "BottlingPlant.h"

_Task Truck {
    Printer &prt;
    NameServer &nameServer;
    BottlingPlant &plant;
    unsigned int numVendingMachines;
    unsigned int maxStockPerFlavour;
    void main();
  public:
    Truck( Printer &prt, NameServer &nameServer, BottlingPlant &plant,
           unsigned int numVendingMachines, unsigned int maxStockPerFlavour );
};

#endif

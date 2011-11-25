#ifndef TRUCK_
#define TRUCK_

#include "NameServer.h"
#include "BottlingPlant.h"

_Task Truck {
    void main();
  public:
    Truck( Printer &prt, NameServer &nameServer, BottlingPlant &plant,
           unsigned int numVendingMachines, unsigned int maxStockPerFlavour );
};

#endif

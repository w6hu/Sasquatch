#ifndef TRUCK_
#define TRUCK_

#include <uC++.h>

#include "NameServer.h"
#include "BottlingPlant.h"

_Task Truck {
    static const unsigned int NUM_FLAVOURS = 4;
    Printer &prt;
    NameServer &nameServer;
    BottlingPlant &plant;
    unsigned int numVendingMachines;
    unsigned int maxStockPerFlavour;
    unsigned int cargo[NUM_FLAVOURS];
    unsigned int cargoSize();
    void main();
  public:
    Truck( Printer &prt, NameServer &nameServer, BottlingPlant &plant,
           unsigned int numVendingMachines, unsigned int maxStockPerFlavour );
};

#endif

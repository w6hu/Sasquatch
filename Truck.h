#ifndef TRUCK_
#define TRUCK_

#include <uC++.h>

#include "NameServer.h"
#include "BottlingPlant.h"

_Task Truck {
    static const unsigned int NUM_FLAVOURS = 4;            // # flavours
    Printer &prt;                                          // reference to Printer
    NameServer &nameServer;                                // reference to NameServer
    BottlingPlant &plant;                                  // reference to Bottling Plant
    unsigned int numVendingMachines;                       // # vending machines
    unsigned int maxStockPerFlavour;                       // max # bottles stocked for a flavour
    unsigned int cargo[NUM_FLAVOURS];                      // array to hold the bottles to be delivered
    unsigned int cargoSize();                              // helper function to count the # bottles to be delivered
    void main();
  public:
    Truck( Printer &prt, NameServer &nameServer, BottlingPlant &plant,
           unsigned int numVendingMachines, unsigned int maxStockPerFlavour );
};

#endif

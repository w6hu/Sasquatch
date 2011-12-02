#ifndef BOTTLING_
#define BOTTLING_

#include <uC++.h>
#include "Printer.h"
#include "NameServer.h"
#include "VendingMachine.h"

_Task BottlingPlant {
    Printer &prt;                                          // reference to Printer
    NameServer &nameServer;                                // reference to NameServer
    unsigned int numVendingMachines;                       // # vending machines
    unsigned int maxShippedPerFlavour;                     // max # bottles shipped per flavour
    unsigned int maxStockPerFlavour;                       // max # bottles stocked for a flavour
    unsigned int timeBetweenShipments;                     // time between truck deliveries
    unsigned int produced[VendingMachine::NUM_FLAVOURS];   // array to hold produced bottles
    bool closingDown;                                      // flag to indicate whether plant is shutting down
    void productionRun();                                  // helper function that simulates a production run
    unsigned int numProduced();                            // helper function that counts # bottles produced
    void main();
  public:
    BottlingPlant( Printer &prt, NameServer &nameServer, unsigned int numVendingMachines,
                 unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
                 unsigned int timeBetweenShipments );
    ~BottlingPlant();
    bool getShipment( unsigned int cargo[] );
};

#endif

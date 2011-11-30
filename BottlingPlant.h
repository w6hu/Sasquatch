#ifndef BOTTLING_
#define BOTTLING_

#include <uC++.h>
#include "Printer.h"
#include "NameServer.h"

_Task BottlingPlant {
    static const unsigned int NUM_FLAVOURS = 4;
    Printer &prt;
    NameServer &nameServer;
    unsigned int numVendingMachines;
    unsigned int maxShippedPerFlavour;
    unsigned int maxStockPerFlavour;
    unsigned int timeBetweenShipments;
    unsigned int produced[NUM_FLAVOURS];
    bool closingDown;
    void main();
    void productionRun();
    unsigned int numProduced();
  public:
    BottlingPlant( Printer &prt, NameServer &nameServer, unsigned int numVendingMachines,
                 unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
                 unsigned int timeBetweenShipments );
    ~BottlingPlant();
    bool getShipment( unsigned int cargo[] );
};

#endif

#include "BottlingPlant.h"

BottlingPlant::BottlingPlant( Printer &prt, NameServer &nameServer, unsigned int numVendingMachines,
                              unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
                              unsigned int timeBetweenShipments ) :
  prt(prt), nameServer(nameServer)
{
    this->numVendingMachines = numVendingMachines;
    this->maxShippedPerFlavour = maxShippedPerFlavour;
    this->maxStockPerFlavour = maxStockPerFlavour;
    this->timeBetweenShipments = timeBetweenShipments;
}

bool BottlingPlant::getShipment( unsigned int cargo[] )
{
    // dummy
    return true;
}

void BottlingPlant::main()
{
    // dummy
    return;
}



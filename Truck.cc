#include "Truck.h"

Truck::Truck( Printer &prt, NameServer &nameServer, BottlingPlant &plant,
              unsigned int numVendingMachines, unsigned int maxStockPerFlavour ) :
  prt(prt), nameServer(nameServer), plant(plant)
{
    this->numVendingMachines = numVendingMachines;
    this->maxStockPerFlavour = maxStockPerFlavour;
}

void Truck::main()
{

}



#include "VendingMachine.h"

VendingMachine::VendingMachine( Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost,
                                unsigned int maxStockPerFlavour ) :
  prt(prt), nameServer(nameServer)
{
    this->id = id;
    this->sodaCost = sodaCost;
    this->maxStockPerFlavour = maxStockPerFlavour;
}

VendingMachine::Status VendingMachine::buy( Flavours flavour, WATCard &card )
{
    // dummy
    return VendingMachine::BUY;
}

unsigned int *VendingMachine::inventory()
{
    // dummy
    return 0;
}

void VendingMachine::restocked()
{
    // dummy
    return;
}

_Nomutex unsigned int VendingMachine::cost()
{
    return sodaCost;
}

_Nomutex unsigned int VendingMachine::getId()
{
    return id;
}

void VendingMachine::main()
{
    // dummy
    return;
}



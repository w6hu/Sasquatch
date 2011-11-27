#include "NameServer.h"

NameServer::NameServer( Printer &prt, unsigned int numVendingMachines, unsigned int numStudents ) :
  prt(prt)
{
    this->numVendingMachines = numVendingMachines;
    this->numStudents = numStudents;
}

void NameServer::VMregister( VendingMachine *vendingmachine )
{
    // dummy
    return;
}

VendingMachine *NameServer::getMachine( unsigned int id )
{
    // dummy
    return NULL; 
}

VendingMachine **NameServer::getMachineList()
{
    // dummy
    return NULL; 
}

void NameServer::main()
{
    // dummy
    return; 
}



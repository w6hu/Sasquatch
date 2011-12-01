#ifndef NAMESERVER_
#define NAMESERVER_

#include <uC++.h>
#include "Printer.h"

_Task VendingMachine;          // fwd declaration to break circular dependency with NameServer.h

_Task NameServer {
    Printer &prt;
    unsigned int numVendingMachines;
    unsigned int numStudents;
    VendingMachine **machineList;
    unsigned int *studMachAssign;
    unsigned int registerOrder;
    void main();
  public:
    NameServer( Printer &prt, unsigned int numVendingMachines, unsigned int numStudents );
    ~NameServer();
    void VMregister( VendingMachine *vendingmachine );
    VendingMachine *getMachine( unsigned int id );
    VendingMachine **getMachineList();
};

#endif

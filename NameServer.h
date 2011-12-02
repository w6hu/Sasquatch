#ifndef NAMESERVER_
#define NAMESERVER_

#include <uC++.h>
#include "Printer.h"

_Task VendingMachine;                                      // fwd declaration to break circular dependency

_Task NameServer {
    Printer &prt;                                          // reference to Printer
    unsigned int sid;
    unsigned int mid;
    unsigned int numVendingMachines;                       // # vending machines
    unsigned int numStudents;                              // # students
    VendingMachine **machineList;                          // list of registered vending machines
    unsigned int *studMachAssign;                          // map students to vending machines
    unsigned int registerOrder;                            // keep track of registration order
    void main();
  public:
    NameServer( Printer &prt, unsigned int numVendingMachines, unsigned int numStudents );
    ~NameServer();
    void VMregister( VendingMachine *vendingmachine );
    VendingMachine *getMachine( unsigned int id );
    VendingMachine **getMachineList();
};

#endif

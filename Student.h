#ifndef STUDENT_
#define STUDENT_

#include <uC++.h>
#include "NameServer.h"
#include "WATCardOffice.h"
#include "VendingMachine.h"
_Task Student {
    //private members
    Printer &prt;
    NameServer &nameServer;
    WATCardOffice &cardOffice;
    unsigned int id;
    unsigned int maxPurchases;
    void main();
  public:
    Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, unsigned int id,
             unsigned int maxPurchases );
};

#endif

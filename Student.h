#ifndef STUDENT_
#define STUDENT_

#include <uC++.h>
#include "NameServer.h"
#include "WATCardOffice.h"

_Task Student {
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

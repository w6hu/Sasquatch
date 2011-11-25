#ifndef STUDENT_
#define STUDENT_

#include "NameServer.h"
#include "WATCardOffice.h"

_Task Student {
    void main();
  public:
    Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, unsigned int id,
             unsigned int maxPurchases );
};

#endif

#ifndef PARENT_
#define PARENT_

#include <uC++.h>
#include "Printer.h"
#include "Bank.h"

_Task Parent {
    Printer &prt;
    Bank &bank;
    unsigned int numStudents;
    unsigned int parentalDelay;
    void main();
  public:
    Parent( Printer &prt, Bank &bank, unsigned int numStudents, unsigned int parentalDelay );
    ~Parent();
};

#endif

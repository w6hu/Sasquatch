#ifndef PARENT_
#define PARENT_

#include "Printer.h"

_Task Parent {
    void main();
  public:
    Parent( Printer &prt, Bank &bank, unsigned int numStudents, unsigned int parentalDelay );
};

#endif

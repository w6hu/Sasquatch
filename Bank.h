#ifndef BANK_
#define BANK_

#include <uC++.h>

_Monitor Bank {
    unsigned int numStudents;
  public:
    Bank( unsigned int numStudents );
    void deposit( unsigned int id, unsigned int amount );
    void withdraw( unsigned int id, unsigned int amount );
};

#endif

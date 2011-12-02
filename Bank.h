#ifndef BANK_
#define BANK_

#include <uC++.h>

_Monitor Bank {
    unsigned int numStudents;
    int *accounts;
    uCondition noFund;
  public:
    Bank( unsigned int numStudents );
    ~Bank();
    void deposit( unsigned int id, unsigned int amount );
    void withdraw( unsigned int id, unsigned int amount );
};

#endif

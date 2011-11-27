#include "Parent.h"

Parent::Parent( Printer &prt, Bank &bank, unsigned int numStudents, unsigned int parentalDelay ) :
  prt(prt), bank(bank)
{
    this->numStudents = numStudents;
    this->parentalDelay = parentalDelay;
}

void Parent::main()
{

}


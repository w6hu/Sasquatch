#include "Student.h"

Student::Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, unsigned int id,
                  unsigned int maxPurchases ) :
  prt(prt), nameServer(nameServer), cardOffice(cardOffice)
{
    this->id = id;
    this->maxPurchases = maxPurchases;
}

void Student::main()
{

}



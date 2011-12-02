#include "Parent.h"
#include "MPRNG.h"
#include <iostream>
extern MPRNG mprng;

Parent::Parent( Printer &prt, Bank &bank, unsigned int numStudents, unsigned int parentalDelay ) :
  prt(prt), bank(bank)
{
    this->numStudents = numStudents;
    this->parentalDelay = parentalDelay;
}

Parent::~Parent() {}

void Parent::main()
{
    prt.print(Printer::Parent, 'S');

    for (;;) {
        _Accept(~Parent) {
            break;
        } else {
            yield(parentalDelay);

            int student = mprng() % numStudents;
            int gift = mprng() % 3 + 1;
            bank.deposit(student, gift);
           // std::cout<<"student"<<student<<" ,gift"<<gift<<std::endl;
            prt.print(Printer::Parent, 'D', student, gift);
        }
    }

    prt.print(Printer::Parent, 'F');
}


#ifndef WATCARDOFFICE_
#define WATCARDOFFICE_

#include <uC++.h>
#include "WATCard.h"
#include "Printer.h"
#include "Bank.h"

_Task WATCardOffice {
    struct Job {				// marshalled arguments and return future
	//Args args;				// call arguments (YOU DEFINE "Args")
	FWATCard result;			// return future
	Job();   // dummy default constructor: what params do I need???
        //Job( Args args ) : args( args ) {}
    };
    _Task Courier {                             // communicates with bank
	//Args args;				// call arguments (YOU DEFINE "Args")
        void main();
      public:
        Courier(); // dummy default constructor: what params does this need??
        //Courier( Args args ) : args( args ) {}
    };

    Printer &prt;
    Bank &bank;
    unsigned int numCouriers;
    void main();
  public:
    _Event Lost {};
    WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers );
    FWATCard create( unsigned int sid, unsigned int amount, WATCard *&card );
    FWATCard transfer( unsigned int sid, unsigned int amount, WATCard *card );
    Job *requestWork();
};
#endif


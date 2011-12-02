#ifndef WATCARDOFFICE_
#define WATCARDOFFICE_

#include <uC++.h>
#include <queue>
#include "WATCard.h"
#include "Printer.h"
#include "Bank.h"

_Task WATCardOffice {
    struct Job {				// marshalled arguments and return future
        unsigned int sid;
        unsigned int amount;        // call arguments (YOU DEFINE "Args")
        FWATCard result;			// return future
        Job(unsigned int sid, unsigned int amount, FWATCard result): sid(sid), amount(amount), result(result){}  
    };
    _Task Courier {                             // communicates with bank
        		// call arguments 
        WATCardOffice *office;
        void main();
        public:
        Courier(WATCardOffice * office):office(office){} // default constructor 
    };
    std::queue<Job*> jobQueue;
    uCondition jobEmpty;
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


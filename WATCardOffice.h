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
        WATCard* card;
        Job(unsigned int sid, unsigned int amount, WATCard* card): sid(sid), amount(amount),card(card){}  
    };
    _Task Courier {                             // communicates with bank
        		// call arguments 
        WATCardOffice *office;
        Printer & prt;
        unsigned int id;
        void main();
        public:
        Courier(WATCardOffice * office, Printer& prt, unsigned int id):office(office), prt(prt), id(id){} // default constructor 
    };
    std::queue<Job*> jobQueue;
    Printer &prt;
    Bank &bank;
    unsigned int sid;
    unsigned int amount;
    unsigned int numCouriers;
    void main();
    uCondition noJob;
    public:
    _Event Lost {};
    WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers );
    FWATCard create( unsigned int sid, unsigned int amount, WATCard *&card );
    FWATCard transfer( unsigned int sid, unsigned int amount, WATCard *card );
    Job *requestWork();
};
#endif


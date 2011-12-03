#ifndef WATCARDOFFICE_
#define WATCARDOFFICE_

#include <uC++.h>
#include <queue>
#include "WATCard.h"
#include "Printer.h"
#include "Bank.h"

_Task WATCardOffice {
    struct Job {			                    	                    // marshalled arguments and return future
        unsigned int sid;
        unsigned int amount;                                            // call arguments
        FWATCard result;			                                    // returns future
        WATCard* card;                                                  
        Job(unsigned int sid, unsigned int amount, WATCard* card): sid(sid), amount(amount),card(card){}  
    };//Job
    _Task Courier {                                                     // communicates with bank
        WATCardOffice *office;                                          // call arguments
        Printer & prt;
        unsigned int id;
        void main();
        public:
        Courier(WATCardOffice * office, Printer& prt, unsigned int id):office(office), prt(prt), id(id){} // default constructor 
    };//Courier
    std::queue<Job*> jobQueue;                                          // store all unfinished jobs
    Printer &prt;
    Bank &bank;
    unsigned int sid;
    unsigned int amount;
    unsigned int numCouriers;
    void main();
    public:
    _Event Lost {};
    WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers );
    FWATCard create( unsigned int sid, unsigned int amount, WATCard *&card );
    FWATCard transfer( unsigned int sid, unsigned int amount, WATCard *card );
    Job *requestWork();
};//WATCardOffice
#endif


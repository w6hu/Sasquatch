#include "WATCardOffice.h"

WATCardOffice::WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers ) :
  prt(prt), bank(bank)
{
    this->numCouriers = numCouriers;
}

FWATCard WATCardOffice::create( unsigned int sid, unsigned int amount, WATCard *&card )
{

}

FWATCard WATCardOffice::transfer( unsigned int sid, unsigned int amount, WATCard *card )
{

}

WATCardOffice::Job *WATCardOffice::requestWork()
{
    // dummy
    return NULL; 
}

void WATCardOffice::main()
{
    // dummy
    return; 
}



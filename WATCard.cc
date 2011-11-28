#include "WATCard.h"

WATCard::WATCard( const WATCard & )			// make private to prevent copying
{
   //no implementation  
}

WATCard &WATCard::operator=( const WATCard & )		// make private to prevent copying
{
    //no implementation
}

WATCard::WATCard()
{
    balance = 0;
}

void WATCard::deposit( unsigned int amount )
{
    balance += amount;
}

void WATCard::withdraw( unsigned int amount )
{
    balance -= amount;
}

unsigned int WATCard::getBalance()
{
    return balance;
}



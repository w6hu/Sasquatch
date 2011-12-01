#include "WATCard.h"

WATCard::WATCard( const WATCard &card )			// make private to prevent copying
{
   balance = card.balance; 
}

WATCard &WATCard::operator=( const WATCard &card )	// make private to prevent assignment
{
    balance = card.balance; 
    return *this;
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



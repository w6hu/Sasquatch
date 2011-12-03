#include "WATCard.h"

WATCard::WATCard( const WATCard &card )			// make private to prevent copying
{
   balance = card.balance; 
}//WATCard

WATCard &WATCard::operator=( const WATCard &card )	// make private to prevent assignment
{
    balance = card.balance; 
    return *this;
}//operator=

WATCard::WATCard()
{
    balance = 0;
}//WATCard

void WATCard::deposit( unsigned int amount )
{
    balance += amount;
}//deposit

void WATCard::withdraw( unsigned int amount )
{
    balance -= amount;
}//withdraw

unsigned int WATCard::getBalance()
{
    return balance;
}//getBalance



#include "WATCard.h"

WATCard::WATCard( const WATCard & )			// make private to prevent copying
{

}

WATCard &WATCard::operator=( const WATCard & )		// make private to prevent copying
{

}

WATCard::WATCard()
{
    balance = 0;
}

void WATCard::deposit( unsigned int amount )
{

}

void WATCard::withdraw( unsigned int amount )
{

}

unsigned int WATCard::getBalance()
{
    return balance;
}



#ifndef VENDINGMACHINE_
#define VENDINGMACHINE_

#include <uC++.h>
#include "Printer.h"
#include "NameServer.h"
#include "WATCard.h"

_Task VendingMachine {
    Printer &prt;
    NameServer &nameServer;
    unsigned int id;
    unsigned int sodaCost;
    unsigned int maxStockPerFlavour;
    void main();
  public:
    enum Flavours { dummyFlavour1, dummyFlavour2 }; 	// flavours of soda (DUMMYS ATM...*************)
    enum Status { BUY, STOCK, FUNDS };	// purchase status: successful buy, out of stock, insufficient funds
    VendingMachine( Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost,
                    unsigned int maxStockPerFlavour );
    Status buy( Flavours flavour, WATCard &card );
    unsigned int *inventory();
    void restocked();
    _Nomutex unsigned int cost();
    _Nomutex unsigned int getId();
};

#endif

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
    enum Flavours { Flavour0, Flavour1, Flavour2, Flavour3 }; 	// there are 4 flavours of soda
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

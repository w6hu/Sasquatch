#ifndef VENDINGMACHINE_
#define VENDINGMACHINE_

#include <uC++.h>
#include "Printer.h"
#include "NameServer.h"
#include "WATCard.h"

_Task VendingMachine {
    static const unsigned int NUM_FLAVOURS = 4;            // # flavours
    Printer &prt;                                          // reference to Printer
    NameServer &nameServer;                                // reference to NameServer
    unsigned int id;                                       // vending machine id
    unsigned int sodaCost;                                 // cost of bottle
    unsigned int maxStockPerFlavour;                       // max # bottles per flavour that can be stocked
    unsigned int stock[NUM_FLAVOURS];                      // array representing the inventory
    void main();
  public:
    enum Flavours { Blues_Black_Cherry=0, 
                    Classical_Cream_Soda=1, 
                    Rock_Root_Beer=2, 
                    Jazz_Lime=3 }; 	                   // there are 4 flavours of soda
    enum Status { BUY, STOCK, FUNDS };	                   // successful purchase, out of stock, insufficient funds
    VendingMachine( Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost,
                    unsigned int maxStockPerFlavour );
    ~VendingMachine();
    Status buy( Flavours flavour, WATCard &card );
    unsigned int *inventory();
    void restocked();
    _Nomutex unsigned int cost();
    _Nomutex unsigned int getId();
};

#endif

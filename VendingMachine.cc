#include "VendingMachine.h"

VendingMachine::VendingMachine( Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost,
                                unsigned int maxStockPerFlavour ) :
  prt(prt), nameServer(nameServer)
{
    this->id = id;                                                   // assign passed in variables
    this->sodaCost = sodaCost;
    this->maxStockPerFlavour = maxStockPerFlavour;

    for (unsigned int i = 0; i < VendingMachine::NUM_FLAVOURS; i++) { // initialization: empty inventory
        stock[i] = 0;
    }
    nameServer.VMregister(this);                                     // register this machine with name server
}

VendingMachine::~VendingMachine() {};                                // destructor

VendingMachine::Status VendingMachine::buy( Flavours flavour, WATCard &card )
{
    int index = (int)flavour;                                        // inventory is grouped by flavour

    if (stock[index] == 0) {                                         // no more bottles of the specified flavour
        return VendingMachine::STOCK;
    }
    else if (card.getBalance() < sodaCost) {                         // not enough money on WATCard
        return VendingMachine::FUNDS;
    }
    else {                                                           // enough money + flavour is in stock
        card.withdraw(sodaCost);                                     // debit the WATCard
        stock[index]--;                                              // decrease the # stock for specified flavour
        prt.print(Printer::Vending, id, 'B', index, stock[index]);       // send data to printer (student bought soda)
        return VendingMachine::BUY;
    }
}

unsigned int *VendingMachine::inventory()                            // return current inventory
{
    return (unsigned int *)stock;
}

void VendingMachine::restocked()                                     // used by truck to signal end of restocking
{
    return;
}

_Nomutex unsigned int VendingMachine::cost()                         // query cost of soda
{
    return sodaCost;
}

_Nomutex unsigned int VendingMachine::getId()                        // query vending machine id
{
    return id;
}

void VendingMachine::main()
{

    prt.print(Printer::Vending, id, 'S', sodaCost);                      // send data to printer (vending machine start)

    for (;;) {
        _Accept(~VendingMachine) {                                   // accept destructor
            break;
        } or _Accept(inventory) {                                    // accept truck deliveries from bottling plant
            prt.print(Printer::Vending, id, 'r');                        // send data to printer (start restocking)
            _Accept(restocked);                                      // wait until truck finishes restocking
            prt.print(Printer::Vending, id, 'R');                        // send data to printer (finished restocking)
        } or _Accept(buy) {}                                         // allow students to buy soda
    } // for
#include <iostream>
  //  std::cout<<"id="<<id<<std::endl;
    prt.print(Printer::Vending, id, 'F');                                // send data to printer (vending machine finished)
}



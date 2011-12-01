#include "VendingMachine.h"

const unsigned int VendingMachine::NUM_FLAVOURS;

VendingMachine::VendingMachine( Printer &prt, NameServer &nameServer, unsigned int id, unsigned int sodaCost,
                                unsigned int maxStockPerFlavour ) :
  prt(prt), nameServer(nameServer)
{
    this->id = id;
    this->sodaCost = sodaCost;
    this->maxStockPerFlavour = maxStockPerFlavour;

    for (unsigned int i = 0; i < NUM_FLAVOURS; i++) {
        stock[i] = 0;
    }
}

VendingMachine::~VendingMachine() {};

VendingMachine::Status VendingMachine::buy( Flavours flavour, WATCard &card )
{
    int index = (int)flavour;

    if (stock[index] == 0) {
        return VendingMachine::STOCK;
    }
    else if (card.getBalance() < sodaCost) {
        return VendingMachine::FUNDS;
    }
    else {
        card.withdraw(sodaCost);
        stock[index]--;
        prt.print(Printer::Vending, 'B', index, stock[index]);
        return VendingMachine::BUY;
    }
}

unsigned int *VendingMachine::inventory()
{
    return (unsigned int *)stock;
}

void VendingMachine::restocked()
{
    return;
}

_Nomutex unsigned int VendingMachine::cost()
{
    return sodaCost;
}

_Nomutex unsigned int VendingMachine::getId()
{
    return id;
}

void VendingMachine::main()
{
    // register with nameServer
    nameServer.VMregister(this);

    prt.print(Printer::Vending, 'S', sodaCost);

    for (;;) {
        _Accept(~VendingMachine) {
            break;
        } or _Accept(inventory) {
            prt.print(Printer::Vending, 'r');
            _Accept(restocked);
            prt.print(Printer::Vending, 'R');
        } or _Accept(buy) {}
    }

    prt.print(Printer::Vending, 'F');
}



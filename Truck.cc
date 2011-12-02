#include "Truck.h"
#include "MPRNG.h"
#include "VendingMachine.h"

extern MPRNG mprng;

Truck::Truck( Printer &prt, NameServer &nameServer, BottlingPlant &plant,
              unsigned int numVendingMachines, unsigned int maxStockPerFlavour ) :
  prt(prt), nameServer(nameServer), plant(plant)
{
    this->numVendingMachines = numVendingMachines;                   // assign passed in variables
    this->maxStockPerFlavour = maxStockPerFlavour;

    for (unsigned int i = 0; i < VendingMachine::NUM_FLAVOURS; i++) { // initialization: nothing to deliver yet
        cargo[i] = 0;
    }
}

unsigned int Truck::cargoSize()                                      // helper function to count # bottles in cargo
{
    unsigned int count = 0;

    for (unsigned int i = 0; i < VendingMachine::NUM_FLAVOURS; i++) { // sum over all bottles of all flavours
        count += cargo[i];
    }

    return count;
}

void Truck::main()
{
    prt.print(Printer::Truck, 'S');                                  // send data to printer (truck is starting)

    VendingMachine **machList = nameServer.getMachineList();         // get the list of vending machines

    for (;;) {
        int coffeeTime = mprng() % 10 + 1;
        yield(coffeeTime);                                           // get coffee from Tim Hortons

        bool status = plant.getShipment(cargo);                      // load cargo from bottling plant
        prt.print(Printer::Truck, 'P', cargoSize());                 // send data to printer (truck loading up cargo)

        if (status) break;                                           // if plant is shutting down, break to terminate
        for (unsigned int vend = 0; vend < numVendingMachines; vend++) { // loop through all vending machines on list
            prt.print(Printer::Truck, 'd', 
                      machList[vend]->getId(), cargoSize());         // send data to printer (begin delivery)

            unsigned int *inventory = machList[vend]->inventory();   // get vending machine inventory
            unsigned int num_unreplenished = 0;                      // keep track of # needed to fill vending machine
            for (unsigned int i = 0; i < VendingMachine::NUM_FLAVOURS; i++) { // loop through all flavours
                unsigned int space = maxStockPerFlavour - inventory[i]; // calculate # needed to fill up to max stock
                if (cargo[i] >= space) {                             // if enough cargo to fill up vending machine
                    cargo[i] -= space;                               // decrease cargo
                    inventory[i] = maxStockPerFlavour;               // max out vending machine stock
                }
                else {                                               // if cannot fully restock vending machine
                    num_unreplenished += space - cargo[i];           // update # bottles needed to fill vending machine

                    inventory[i] += cargo[i];                        // restock as much as possible
                    cargo[i] = 0;                                    // empty cargo
                }
            } // flavour for loop
            machList[vend]->restocked();                             // tell vending machine we are done restocking

            if (num_unreplenished > 0) {                             // if vending machine is not fully restocked
                prt.print(Printer::Truck, 'U', 
                          machList[vend]->getId(), num_unreplenished); // send data to printer (unsuccessfully filled)
            }

            prt.print(Printer::Truck, 'D', 
                      machList[vend]->getId(), cargoSize());         // send data to printer (end delivery)

            if (cargoSize() == 0) {                                  // end delivery if we run out of cargo
                break;
            }
        } // vending machine list for loop
    } // infinite for loop

    prt.print(Printer::Truck, 'F');                                  // send data to printer (truck finished)                       
}



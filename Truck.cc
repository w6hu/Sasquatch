#include "Truck.h"
#include "MPRNG.h"
#include "VendingMachine.h"

extern MPRNG mprng;

const unsigned int Truck::NUM_FLAVOURS;

Truck::Truck( Printer &prt, NameServer &nameServer, BottlingPlant &plant,
              unsigned int numVendingMachines, unsigned int maxStockPerFlavour ) :
  prt(prt), nameServer(nameServer), plant(plant)
{
    this->numVendingMachines = numVendingMachines;
    this->maxStockPerFlavour = maxStockPerFlavour;

    for (unsigned int i = 0; i < NUM_FLAVOURS; i++) {
        cargo[i] = 0;
    }
}

unsigned int Truck::cargoSize()
{
    unsigned int tempSize = 0;

    for (unsigned int i = 0; i < NUM_FLAVOURS; i++) {
        tempSize += cargo[i];
    }

    return tempSize;
}

void Truck::main()
{
    prt.print(Printer::Truck, 'S');

    VendingMachine **machList = nameServer.getMachineList();

    for (;;) {
        int coffeeTime = mprng() % 10 + 1;       // random time need to get coffee
        yield(coffeeTime);

        bool status = plant.getShipment(cargo);  // cargo will be overwritten (ie. existing cargo thrown away)
        prt.print(Printer::Truck, 'P', cargoSize());

        if (status) break;                       // if plant is shutting down, terminate
        for (unsigned int vend = 0; vend < numVendingMachines; vend++) {
            prt.print(Printer::Truck, 'd', machList[vend]->getId(), cargoSize());

            unsigned int *inventory = machList[vend]->inventory();
            unsigned int num_unreplenished = 0;
            for (unsigned int i = 0; i < NUM_FLAVOURS; i++) {
                unsigned int space = maxStockPerFlavour - inventory[i];
                if (cargo[i] >= space) {
                    cargo[i] -= space;
                    inventory[i] = maxStockPerFlavour;
                }
                else {
                    // not fully restocked
                    num_unreplenished += space - cargo[i];

                    inventory[i] += cargo[i];
                    cargo[i] = 0;
                }
            } // for
            machList[vend]->restocked();

            if (num_unreplenished > 0) {
                prt.print(Printer::Truck, 'U', machList[vend]->getId(), num_unreplenished);
            }

            prt.print(Printer::Truck, 'B', machList[vend]->getId(), cargoSize());

            if (cargoSize() == 0) {
                break;
            }
        } // for
    }

    prt.print(Printer::Truck, 'F');
}



#include "BottlingPlant.h"
#include "MPRNG.h"
#include "Truck.h"

extern MPRNG mprng;

const unsigned int BottlingPlant::NUM_FLAVOURS;

BottlingPlant::BottlingPlant( Printer &prt, NameServer &nameServer, unsigned int numVendingMachines,
                              unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
                              unsigned int timeBetweenShipments ) :
  prt(prt), nameServer(nameServer)
{
    this->numVendingMachines = numVendingMachines;
    this->maxShippedPerFlavour = maxShippedPerFlavour;
    this->maxStockPerFlavour = maxStockPerFlavour;
    this->timeBetweenShipments = timeBetweenShipments;

    closingDown = false;

    for (unsigned int i = 0; i < NUM_FLAVOURS; i++) {
        produced[i] = 0;
    }
}

BottlingPlant::~BottlingPlant() {}

void BottlingPlant::productionRun()
{
    // yield to simulate time for production
    yield(timeBetweenShipments);

    // for each flavour
    for (unsigned int i = 0; i < NUM_FLAVOURS; i++) {
        produced[i] = mprng() % (maxShippedPerFlavour + 1);       // produce random number of bottles
    }
}

bool BottlingPlant::getShipment( unsigned int cargo[] )
{
    if (closingDown) return true;
    else {
        // load cargo
        for (unsigned int i = 0; i < NUM_FLAVOURS; i++) {
            cargo[i] = produced[i];
        }
    }
    return false;
}

unsigned int BottlingPlant::numProduced()
{
    unsigned int count = 0;

    for (unsigned int i = 0; i < NUM_FLAVOURS; i++) {
        count += produced[i];
    }

    return count;
}

void BottlingPlant::main()
{
    prt.print(Printer::BottlingPlant, 'S');

    // create truck task
    Truck *truck = new Truck(prt, nameServer, *this, numVendingMachines, maxStockPerFlavour);

    // initial production
    productionRun();

    prt.print(Printer::BottlingPlant, 'G', numProduced());

    for (;;) {
        _Accept(~BottlingPlant) {
            closingDown = true;
            break;
        } or _Accept(getShipment) {    // wait for truck to load up cargo
            prt.print(Printer::BottlingPlant, 'P');

            // start another production run once truck leaves
            productionRun();

            prt.print(Printer::BottlingPlant, 'G', numProduced());
        }
    }
    
    // destructor called; cleanup
    delete truck;

    prt.print(Printer::BottlingPlant, 'F');
}



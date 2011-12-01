#include "BottlingPlant.h"
#include "MPRNG.h"
#include "Truck.h"

extern MPRNG mprng;

const unsigned int BottlingPlant::NUM_FLAVOURS;                      // initialize constant

BottlingPlant::BottlingPlant( Printer &prt, NameServer &nameServer, unsigned int numVendingMachines,
                              unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
                              unsigned int timeBetweenShipments ) :
  prt(prt), nameServer(nameServer)
{
    this->numVendingMachines = numVendingMachines;                   // assign passed in variables
    this->maxShippedPerFlavour = maxShippedPerFlavour;
    this->maxStockPerFlavour = maxStockPerFlavour;
    this->timeBetweenShipments = timeBetweenShipments;

    closingDown = false;                                             // unset flag

    for (unsigned int i = 0; i < NUM_FLAVOURS; i++) {                // initialization: nothing produced yet
        produced[i] = 0;
    }
}

BottlingPlant::~BottlingPlant() {}                                   // destructor

void BottlingPlant::productionRun()                                  // helper function to simulate a production run
{
    yield(timeBetweenShipments);                                     // yield to simulate time for production

    for (unsigned int i = 0; i < NUM_FLAVOURS; i++) {                // loop through each flavour
        produced[i] = mprng() % (maxShippedPerFlavour + 1);          // produce random number of bottles
    }
}

bool BottlingPlant::getShipment( unsigned int cargo[] )              // called by Truck to load the produced bottles
{
    if (closingDown) return true;                                    // is plant shutting down?

    for (unsigned int i = 0; i < NUM_FLAVOURS; i++) {                // otherwise, load the cargo
        cargo[i] = produced[i];
    }
    return false;
}

unsigned int BottlingPlant::numProduced()                            // helper function that returns # bottles produced
{
    unsigned int count = 0;

    for (unsigned int i = 0; i < NUM_FLAVOURS; i++) {                // sum over # bottles of all flavours produced
        count += produced[i];
    }

    return count;
}

void BottlingPlant::main()
{
    prt.print(Printer::BottlingPlant, 'S');                          // send data to printer (plant is starting)

    Truck *truck = new Truck(prt, nameServer, *this,                 // create truck task    
                             numVendingMachines, 
                             maxStockPerFlavour);

    productionRun();                                                 // initial production run

    prt.print(Printer::BottlingPlant, 'G', numProduced());           // send data to printer (produced X bottles)

    for (;;) {
        _Accept(~BottlingPlant) {                                    // accept destructor
            closingDown = true;                                      // set flag so truck knows plant is shutting down
            _Accept(getShipment);                                    // wait for truck to finish final delivery
            break;
        } or _Accept(getShipment) {                                  // accept truck to load up cargo
            prt.print(Printer::BottlingPlant, 'P');                  // send data to printer (starting production run)

            productionRun();                                         // start another production run once truck leaves

            prt.print(Printer::BottlingPlant, 'G', numProduced());   // send data to printer (produced X bottles)
        }
    }
    
    delete truck;                                                    // delete truck task

    prt.print(Printer::BottlingPlant, 'F');                          // send data to printer (plant finished)
}



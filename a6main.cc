#include <uC++.h>
#include <iostream>
#include <sstream>
#include <ctime>
#include "Printer.h"
#include "ProcessConfigFile.h"
#include "Bank.h"
#include "Parent.h"
#include "WATCardOffice.h"
#include "NameServer.h"
#include "VendingMachine.h"
#include "BottlingPlant.h"
#include "Student.h"
#include "MPRNG.h"

using namespace std;

MPRNG mprng;

bool convert( int &val, char *buffer ) {		                     // convert C string to integer
    std::stringstream ss( buffer );			                     // connect stream and buffer
    ss >> dec >> val;					                     // convert integer from buffer
    return ! ss.fail() &&				                     // conversion successful ?
	// characters after conversion all blank ?
	string( buffer ).find_first_not_of( " ", ss.tellg() ) == string::npos;
} // convert

void usage( char *argv[] ) {
    cerr << "Usage: " << argv[0]
	 << " [ config-file"
	 << " [ random-seed (> 0) ] ]" << endl;
    exit( EXIT_FAILURE );				                     // TERMINATE
} // usage

void uMain::main() {
    // initialize to default values
    ConfigParms configParameters;
    const char *configFile = "soda.config";
    int seed = 0;

    switch ( argc ) {
        case 3:
            if ( ! convert( seed, argv[2] ) || seed <= 0 ) {	             // invalid seed
	        usage( argv );
	    } // if
            // FALL THROUGH
        case 2:
            configFile = argv[1];
            // FALL THROUGH
        case 1:                                                              // use default values
            break;
        default:						             // wrong # of options
	    usage( argv );
    } // switch

    processConfigFile(configFile, configParameters);                         // extract parameters from config file

    if ( !seed ) {                                                           // if seed is not specified
        seed = time(0);                                                      // initialize seed
    } 

    mprng.seed((uint32_t)seed);                                              // create random number generator
    Printer prt(configParameters.numStudents,
                configParameters.numVendingMachines, 
                configParameters.numCouriers);                               // create Printer Monitor

    Bank bank(configParameters.numStudents);                                 // create Bank Monitor

    Parent *parentTask = new Parent(prt, bank, 
                                    configParameters.numStudents,
                                    configParameters.parentalDelay);         // create Parent Task

    WATCardOffice *WatOff = new WATCardOffice(prt, bank, 
                                              configParameters.numCouriers); // create WatCard Office Administrator

    NameServer *server = new NameServer(prt,
                                        configParameters.numVendingMachines,
                                        configParameters.numStudents);       // create NameServer Task

    VendingMachine *mach[configParameters.numVendingMachines]; 
    for (unsigned int id = 0; id < configParameters.numVendingMachines; id++) {
        mach[id] = new VendingMachine(prt, *server, id, 
                                     configParameters.sodaCost,
                                     configParameters.maxStockPerFlavour );  // create Vending Machine Tasks
    }

    BottlingPlant *plant = new BottlingPlant(prt, *server, 
                                             configParameters.numVendingMachines,
                                             configParameters.maxShippedPerFlavour,
                                             configParameters.maxStockPerFlavour,
                                             configParameters.timeBetweenShipments); // create Bottling Plant Task

    Student *stud[configParameters.numStudents]; 
    for (unsigned int id = 0; id < configParameters.numStudents; id++) {
        stud[id] = new Student(prt, *server, *WatOff, id, 
                               configParameters.maxPurchases);               // create Student Tasks
    }

    for (unsigned int id = 0; id < configParameters.numStudents; id++) {     // termination synchronization
        delete stud[id];
    }

    delete plant;

    for (unsigned int id = 0; id < configParameters.numVendingMachines; id++) { // termination synchronization
        delete mach[id];
    } 

    delete server;
    delete parentTask;
    delete WatOff;

    cout<<"***********************"<<endl;

} // uMain::main


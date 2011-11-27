#include <uC++.h>
#include <iostream>
#include <sstream>
#include <ctime>
#include "Printer.h"
#include "ProcessConfigFile.h"

using namespace std;

bool convert( int &val, char *buffer ) {		                  // convert C string to integer
    std::stringstream ss( buffer );			                  // connect stream and buffer
    ss >> dec >> val;					                  // convert integer from buffer
    return ! ss.fail() &&				                  // conversion successful ?
	// characters after conversion all blank ?
	string( buffer ).find_first_not_of( " ", ss.tellg() ) == string::npos;
} // convert

void usage( char *argv[] ) {
    cerr << "Usage: " << argv[0]
	 << " [ config-file"
	 << " [ random-seed (> 0) ] ]" << endl;
    exit( EXIT_FAILURE );				                  // TERMINATE
} // usage

void uMain::main() {
    // initialize to default values
    ConfigParms configParameters;
    const char *configFile = "soda.config";
    int seed = 0;

    switch ( argc ) {
        case 3:
            if ( ! convert( seed, argv[2] ) || seed <= 0 ) {	          // invalid seed
	        usage( argv );
	    } // if
            // FALL THROUGH
        case 2:
            configFile = argv[1];
            // FALL THROUGH
        case 1:                                                           // use default values
            break;
        default:						          // wrong # of options
	    usage( argv );
    } // switch

    processConfigFile(configFile, configParameters);                      // extract parameters from config file

    if ( !seed ) {                                                        // if seed is not specified
        seed = time(0);                                                   // initialize seed
    } 

    // REST OF CODE YET TO BE WRITTEN!!!

} // uMain::main


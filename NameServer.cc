#include "NameServer.h"
#include "VendingMachine.h"

NameServer::NameServer( Printer &prt, unsigned int numVendingMachines, unsigned int numStudents ) :
  prt(prt)
{
    this->numVendingMachines = numVendingMachines;                   // assign passed in variables
    this->numStudents = numStudents;

    registerOrder = 0;                                               // initialize registration order
    machineList = new VendingMachine *[numVendingMachines];          // create list of vending machines
    studMachAssign = new unsigned int[numStudents];                  // create mapping of students to vending machines
}

NameServer::~NameServer()                                            // destructor
{
    delete[] machineList;                                            // free allocated arrays
    delete[] studMachAssign;
}

void NameServer::VMregister( VendingMachine *vendingmachine )
{
    /* we can technically move everything in this function to main() to increase concurrency;
       however a vending machine can then start before the nameserver actually registers it... */
    machineList[registerOrder++] = vendingmachine;                   // register vending machine
    prt.print(Printer::NameServer, 'R', vendingmachine->getId());    // send data to printer (register vending machine)
}

VendingMachine *NameServer::getMachine( unsigned int id )            // called by Student: match with a vending machine
{
    unsigned int index = studMachAssign[id];                         // index of currently matched machine
    
    studMachAssign[id] = (studMachAssign[id] + 1) % numVendingMachines; // round robin (in preparation for next time)

    prt.print(Printer::NameServer, 'N', 
              (int)id, machineList[index]->getId());                 // send data to printer (new vending machine)

    return machineList[index];                                       // return current matched machine
}

VendingMachine **NameServer::getMachineList()                        // called by Truck: get list of vending machines
{
    return machineList;
}

void NameServer::main()
{
    prt.print(Printer::NameServer, 'S');                             // send data to printer (name server start)

    for (unsigned int i = 0; i < numStudents; i++) {                 // initial assignment of student to machine
        studMachAssign[i] = i % numVendingMachines;
    }

    for (;;) {
        _Accept(~NameServer) {                                       // accept destructor
            break;
        } or _Accept(VMregister) {                                   // accept any mutex member to be called ... 
        } or _Accept(getMachineList) {
        } or _Accept(getMachine) {
        }
    }

    prt.print(Printer::NameServer, 'F');                             // send data to printer (name server finished) 
}



#include "NameServer.h"
#include "VendingMachine.h"

NameServer::NameServer( Printer &prt, unsigned int numVendingMachines, unsigned int numStudents ) :
  prt(prt)
{
    this->numVendingMachines = numVendingMachines;
    this->numStudents = numStudents;

    registerOrder = 0;
    machineList = new VendingMachine *[numVendingMachines];
    studMachAssign = new unsigned int[numStudents];
}

NameServer::~NameServer()
{
    delete[] machineList;
    delete[] studMachAssign;
}

void NameServer::VMregister( VendingMachine *vendingmachine )
{
    machineList[registerOrder++] = vendingmachine;
    prt.print(Printer::NameServer, 'R', vendingmachine->getId());
}

VendingMachine *NameServer::getMachine( unsigned int id )
{
    unsigned int index = studMachAssign[id];
    
    studMachAssign[id] = (studMachAssign[id] + 1) % numVendingMachines;

    prt.print(Printer::NameServer, 'N', (int)id, machineList[index]->getId()); 

    return machineList[index];
}

VendingMachine **NameServer::getMachineList()
{
    return machineList;
}

void NameServer::main()
{
    prt.print(Printer::NameServer, 'S'); 

    // initial assignment of student to machine
    for (unsigned int i = 0; i < numStudents; i++) {
        studMachAssign[i] = i % numVendingMachines;
    }

    for (;;) {
        _Accept(~NameServer) {
            break;
        } or _Accept(VMregister) {

        } or _Accept(getMachineList) {

        } or _Accept(getMachine) {

        }
    }

    prt.print(Printer::NameServer, 'F'); 
}



#include "Printer.h"
#include <iomanip>

using namespace std;

const unsigned int Printer::default_size = 5;

Printer::Printer( unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers )
{
    this->numStudents = numStudents;
    this->numVendingMachines = numVendingMachines;
    this->numCouriers = numCouriers;

    total_tasks = default_size + numStudents + numVendingMachines + numCouriers;

    for (unsigned int i = 0; i < total_tasks; i++) {             // create a packet for each task
        Packet *cur_packet = new Packet();
        cur_packet->kind = sectionedEnum(i);
        cur_packet->empty = true;                                // all packets initially empty
        stored_data.push_back(cur_packet);
    }

    print_headings();                                            // print table heading                   
}

Printer::~Printer()
{
    for (unsigned int i = 0; i < total_tasks; i++) {
        delete stored_data[i];                                   // remove all packets
    }
}

Printer::Kind Printer::sectionedEnum(unsigned int i)
{
    Printer::Kind kind;

    switch (i) {
        case 0:
            kind = Printer::Parent;
            break;
        case 1:
            kind = Printer::WATCardOffice;
            break;
        case 2:
            kind = Printer::NameServer;
            break;
        case 3:
            kind = Printer::Truck;
            break;
        case 4:
            kind = Printer::BottlingPlant;
            break;
        default:
            if (i >= default_size && i < default_size + numStudents)
                kind = Printer::Student;
            else if (i >= default_size + numStudents && i < default_size + numStudents + numVendingMachines)
                kind = Printer::Vending;
            else if (i >= default_size + numStudents + numVendingMachines && i < total_tasks)
                kind = Printer::Courier;
            else
                exit(1);
    }

    return kind;
}

unsigned int Printer::getSectionIndex(Kind kind)
{
    unsigned int index = (unsigned int)kind;

    switch (kind) {
        case Printer::Parent:
        case Printer::WATCardOffice:
        case Printer::NameServer:
        case Printer::Truck:
        case Printer::BottlingPlant:
        case Printer::Student:
            break;
        case Printer::Vending:
            index += (numStudents - 1);
            break;
        case Printer::Courier:
            index += (numVendingMachines + numStudents - 2);
            break;
        default:
            exit(1);
    }

    return index;
}

void Printer::print_headings()
{
    cout << "Parent\t";                                         // print the parent
    cout << "WATOff\t";                                         // print the watcard office
    cout << "Names\t";                                          // print the nameServer
    cout << "Truck\t";                                          // print the truck
    cout << "Plant\t";                                          // print the bottling plant

    for (unsigned int i = 0; i < numStudents; i++) {            // print the students
        cout << "Stud:" << i << "\t";       
    }

    for (unsigned int i = 0; i < numVendingMachines; i++) {     // print the vending machines
        cout << "Mach:" << i << "\t";       
    }

    for (unsigned int i = 0; i < numCouriers; i++) {            // print the couriers
        cout << "Cour:" << i; 
        if (i == numCouriers - 1) break;
        cout << "\t";        
    }
    cout << endl;

    for (unsigned int i = 0; i < total_tasks; i++) {            // print the table separator
        cout << "*******";
        if (i == total_tasks - 1) break;
        cout << "\t";
    }
    cout << endl;
}

void Printer::print_state(unsigned int index)
{
    cout << stored_data[index]->state;                          // print the state

    switch (stored_data[index]->kind) {
      case Printer::Parent:
          switch (stored_data[index]->state) {
              case 'F':
              case 'S':
                  break;
              case 'D':
                  cout << ":" << stored_data[index]->num1;      // print first number associated with state
                  cout << "," << stored_data[index]->num2;      // print second number associated with state
          }
          break;
      case Printer::WATCardOffice:
          switch (stored_data[index]->state) {
              case 'F':
              case 'S':
              case 'W':
                  break;
              case 'C':
              case 'T':
                  cout << ":" << stored_data[index]->num1;      // print first number associated with state
                  cout << "," << stored_data[index]->num2;      // print second number associated with state
          }
          break;
      case Printer::NameServer:
          switch (stored_data[index]->state) {
              case 'F':
              case 'S':
                  break;
              case 'N':
                  cout << ":" << stored_data[index]->num1<<","<<stored_data[index]->num2;      // print first number associated with state
                  break;
              case 'R':
                  cout << ":" << stored_data[index]->num1;      // print second number associated with state
          }
          break;
      case Printer::Truck:
          switch (stored_data[index]->state) {
              case 'F':
              case 'S':
                  break;
              case 'd':
              case 'D':
              case 'U':
                  cout << ":" << stored_data[index]->num1<<","<<stored_data[index]->num2;      // print second number associated with state
                  break; 
              case 'P':
                  cout << ":" << stored_data[index]->num1;      // print second number associated with state
          }
          break;
      case Printer::BottlingPlant:
          switch (stored_data[index]->state) {
              case 'F':
              case 'P':
              case 'S':
                  break;
              case 'G':
                  cout << ":" << stored_data[index]->num1;      // print second number associated with state
          }
          break;
      case Printer::Student:
          switch (stored_data[index]->state) {
              case 'F':
              case 'L':
                  break;
              case 'S':
                  cout << ":" << stored_data[index]->num1<<","<<stored_data[index]->num2;      // print second number associated with state
                  break;
              case 'B':
              case 'V':
                  cout << ":" << stored_data[index]->num1;      // print first number associated with state
          }
          break;
      case Printer::Vending:
          switch (stored_data[index]->state) {
              case 'F':
              case 'r':
              case 'R':
                  break;
              case 'B':
              cout << ":" << stored_data[index]->num1<<","<<stored_data[index]->num2;      // print second number associated with state
                  break;
              case 'S':
                  cout << ":" << stored_data[index]->num1;      // print first number associated with state
          }
          break;
      case Printer::Courier:
          switch (stored_data[index]->state) {
              case 'S':
              case 'F':
                  break;
              case 't':
              case 'T':
                  cout << ":" << stored_data[index]->num1;      // print first number associated with state
                  cout << "," << stored_data[index]->num2;      // print second number associated with state
          }
          break;
      default:
          exit(1);
    }
}

void Printer::flush_immediately()                               // flush all content (only when state = Finished)
{
    unsigned int prev = 0;

    for (unsigned int index = 0; index < total_tasks; index++) {
        if (!stored_data[index]->empty && stored_data[index]->state == 'F') {
            for (; prev < index; prev++)
                cout << "...\t";
            print_state(index);
            stored_data[index]->empty = true;
        }
    }
    for (; prev < total_tasks - 1; prev++)
        cout << "\t...";
    cout << endl;
}

void Printer::flush_overwrite()                                 // flush all content (when overwrite occurs)
{
    unsigned int prev = 0;

    for (unsigned int index = 0; index < total_tasks; index++) {
        if (!stored_data[index]->empty) {
            for (; prev < index; prev++)
                cout << "\t";
            print_state(index);
            stored_data[index]->empty = true;
        }
    }
    cout << endl;
}

void Printer::print( Kind kind, char state )                    // for Parent, WATOff, Names, Truck, Plant
{
    unsigned int id = getSectionIndex(kind);

    if (!stored_data[id]->empty) {                              // flush contents if about to overwrite
        flush_overwrite();
    }
    stored_data[id]->empty = false;                             // write packet
    stored_data[id]->state = state;

    if (state == 'F') {                                         // flush immediately if state = Finished
        flush_immediately();
    }
}

void Printer::print( Kind kind, char state, int value1 )        // for Parent, WATOff, Names, Truck, Plant
{
    unsigned int id = getSectionIndex(kind);

    if (!stored_data[id]->empty) {                              // flush contents if about to overwrite
        flush_overwrite();
    }

    stored_data[id]->empty = false;                             // write packet
    stored_data[id]->state = state;
    stored_data[id]->num1 = value1;
}

void Printer::print( Kind kind, char state, int value1, int value2 ) // for Parent, WATOff, Names, Truck, Plant
{
    unsigned int id = getSectionIndex(kind);

    if (!stored_data[id]->empty) {                              // flush contents if about to overwrite
        flush_overwrite();
    }

    stored_data[id]->empty = false;                             // write packet
    stored_data[id]->state = state;
    stored_data[id]->num1 = value1;
    stored_data[id]->num2 = value2;
}

void Printer::print( Kind kind, unsigned int lid, char state )  // for Stud, Mach, Cour
{
    unsigned int id = getSectionIndex(kind) + lid;

    if (!stored_data[id]->empty) {                              // flush contents if about to overwrite
        flush_overwrite();
    }
    stored_data[id]->empty = false;                             // write packet
    stored_data[id]->state = state;

    if (state == 'F') {                                         // flush immediately if state = Finished
        flush_immediately();
    }
}

void Printer::print( Kind kind, unsigned int lid, char state, int value1 ) // for Stud, Mach, Cour
{
    unsigned int id = getSectionIndex(kind) + lid;
    if (!stored_data[id]->empty) {                              // flush contents if about to overwrite
        flush_overwrite();
    }

    stored_data[id]->empty = false;                             // write packet
    stored_data[id]->state = state;
    stored_data[id]->num1 = value1;
}

void Printer::print( Kind kind, unsigned int lid, char state, int value1, int value2 ) // for Stud, Mach, Cour
{
    unsigned int id = getSectionIndex(kind) + lid;

    if (!stored_data[id]->empty) {                              // flush contents if about to overwrite
        flush_overwrite();
    }

    stored_data[id]->empty = false;                             // write packet
    stored_data[id]->state = state;
    stored_data[id]->num1 = value1;
    stored_data[id]->num2 = value2;
}



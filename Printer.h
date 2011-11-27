#ifndef PRINTER_
#define PRINTER_

#include <uC++.h>
#include <iostream>
#include <vector>

_Monitor Printer {
  public:
    enum Kind { Parent, WATCardOffice, NameServer, Truck, BottlingPlant, Student, Vending, Courier };
    Printer( unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers );
    ~Printer();
    void print( Kind kind, char state );
    void print( Kind kind, char state, int value1 );
    void print( Kind kind, char state, int value1, int value2 );
    void print( Kind kind, unsigned int lid, char state );
    void print( Kind kind, unsigned int lid, char state, int value1 );
    void print( Kind kind, unsigned int lid, char state, int value1, int value2 );
  private:
    struct Packet {                              // structure to hold buffered information for each voter
      public: 
        Kind kind;
        bool empty;                              // whether there is information buffered?
        char state;                              // buffered state
        int num1;                                // buffered value associated with state
        int num2;                                // buffered value associated with state
    };
    void flush_immediately();                    // flush buffer (only when state = Finished)
    void flush_overwrite();                      // flush buffer (only when about to overwrite contents of buffer)
    void print_state(unsigned int index);        // helper function for printing the state
    void print_headings();                       // prints out the column headings
    std::vector<Packet *> stored_data;           // buffer
    unsigned int total_tasks;                    // total number of columns in buffer
    static const unsigned int default_size;
    unsigned int numStudents;
    unsigned int numVendingMachines;
    unsigned int numCouriers;
    unsigned int getSectionIndex(Kind kind);
    Kind sectionedEnum(unsigned int i);
};

#endif

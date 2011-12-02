#include "Bank.h"

Bank::Bank( unsigned int numStudents )
{
    this->numStudents = numStudents;

    accounts = new int[numStudents];
    for (unsigned int i = 0; i < numStudents; i++) {
        accounts[i] = 0;
    }
}

Bank::~Bank()
{
    delete[] accounts;
}

void Bank::deposit( unsigned int id, unsigned int amount )
{
    accounts[id] += amount;
    if (accounts[id] >= 0){
        while (! noFund.empty()){                   //might consider alternatives of using arrays of conditions, each for a student account, so that we can replace while with if
            noFund.signal();
        }
    }
}

void Bank::withdraw( unsigned int id, unsigned int amount )
{
    accounts[id] -= amount;
    while (accounts[id] < 0){
        noFund.wait();
    }
}


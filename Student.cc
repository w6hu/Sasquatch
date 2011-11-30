#include "Student.h"
#include "MPRNG.h"

extern MPRNG mprng;

Student::Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, unsigned int id,
        unsigned int maxPurchases ) :
    prt(prt), nameServer(nameServer), cardOffice(cardOffice)
{
    this->id = id;
    this->maxPurchases = maxPurchases;
}

void Student::main()
{
/*    int r = mprng()% MaxPurchases +1;   //select random number of bottles to buy
    VendingMachine::Flavours favourite = (VendingMachine::Flavours)mprng()%4;
    WATCard* card = new WATCard();
    cardOffice.create(prt, 5, card);            //create initial WATCard
    VendingMachine * myVm = getMachine(id);     //get a vending machine

    for (int i = 0; i < maxPurchases; i++){
        yield(mprng()%10 + 1);              //yield before buying
        VendingMachine::Status status;
        do {
            status = myVm.buy(flavour, card);
            switch ( status ){
                case VendingMachine::BUY:
                    break;
                case VendingMachine::STOCK:
                    vm = nameServer.getMachine(id);     //get a new vm when out of stock
                    break;
                case VendingMachine::FUNDS:
                    try{
                        cardOffice.transfer(id, 5 + sodaCost, card); //may have to block until finished
                    }catch WATCardOffice::LOST{                     //lost card
                        delete(card);
                        card = new WATCard();
                        cardOffice.create(prt, 5, card);
                    }
                    //block student
                    break;
            } 
        }while (status == BUY);
    }
*/
}




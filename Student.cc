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
    int r = mprng()% maxPurchases +1;   //select random number of bottles to buy
    int flavor = mprng() % 4;
    VendingMachine::Flavours favourite;
    switch (flavor){
        case 0:
            favourite = VendingMachine::Blues_Black_Cherry;
            break;
        case 1:
            favourite = VendingMachine::Classical_Cream_Soda;
            break;
        case 2:
            favourite = VendingMachine::Rock_Root_Beer;
            break;
        case 3:
            favourite = VendingMachine::Jazz_Lime;
            break;
        default:
            break;
    }
    WATCard* card = new WATCard();
    cardOffice.create(id, 5, card);            //create initial WATCard
    VendingMachine * myVm = nameServer.getMachine(id);     //get a vending machine

    for (unsigned int i = 0; i < r; i++){
        yield(mprng()%10 + 1);              //yield before buying
        VendingMachine::Status status;
        do {                                //keep buying until succeed
            status = myVm->buy(favourite, *card);
            switch ( status ){
                case VendingMachine::BUY:
                    break;
                case VendingMachine::STOCK:
                    myVm = nameServer.getMachine(id);     //get a new vm when out of stock
                    break;
                case VendingMachine::FUNDS:
                    try{
                        unsigned int cost = myVm->cost();
                        cardOffice.transfer(id, 5 + cost, card); //may have to block until finished
                    }catch (...){                     //lost card
                        delete(card);
                        card = new WATCard();
                        cardOffice.create(id, 5, card);
                    }
                    //block student
                    break;
            } 
        }while (status != VendingMachine::BUY);
    }

}




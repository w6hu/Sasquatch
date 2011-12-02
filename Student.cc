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
    
    unsigned int r = mprng()% maxPurchases +1;   //select random number of bottles to buy
    int flavor = mprng() % 4;
    VendingMachine::Flavours favourite;
    prt.print(Printer::Student, id, 'S', flavor, r);
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
    WATCard * card;
    FWATCard fcard = cardOffice.create(id, 5, card);            //create initial WATCard
    VendingMachine * myVm = nameServer.getMachine(id);     //get a vending machine
    prt.print(Printer::Student, id, 'V', myVm->getId());
    for (unsigned int i = 0; i < r; i++){
        yield(mprng()%10 + 1);              //yield before buying
        VendingMachine::Status status;
        do {                                //keep buying until succeed
            try{
                status = myVm->buy(favourite, *fcard());
                switch ( status ){
                    case VendingMachine::BUY:
                        fcard();
                        prt.print(Printer::Student, id, 'B',((WATCard*)fcard)->getBalance() );
                        break;
                    case VendingMachine::STOCK:
                        myVm = nameServer.getMachine(id);     //get a new vm when out of stock
                        break;
                    case VendingMachine::FUNDS:
                        unsigned int cost = myVm->cost();
                        fcard = cardOffice.transfer(id, 5 + cost, card); //may have to block until finished
                }
            }
            catch (WATCardOffice::Lost &e){
                prt.print(Printer::Student, id, 'L');
                delete(card);
                fcard = cardOffice.create(id, 5, card);
            }
        }while (status != VendingMachine::BUY);
    }
    delete (card);
    prt.print(Printer::Student, id, 'F');
}





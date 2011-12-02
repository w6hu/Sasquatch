#include "WATCardOffice.h"
#include "MPRNG.h"

extern MPRNG mprng;

WATCardOffice::WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers ) :
  prt(prt), bank(bank)
{
    this->numCouriers = numCouriers;
}

FWATCard WATCardOffice::create( unsigned int sid, unsigned int amount, WATCard *&card )
{
    FWATCard card;
    Job * job = new Job(sid, amount, card);
    jobQueue.push(job);                         //insert new job to queue
    jobEmpty.signal();                          //wake up potentially waiting requestWork
    return card;
}

FWATCard WATCardOffice::transfer( unsigned int sid, unsigned int amount, WATCard *card )
{
   // Job * job = new Job(sid, amount, card);
   // jobQueue.push(job);                         //!!!!insert new job to queue
   // jobEmpty.signal();                          //wake up potential waiting requestWork
  //  return card;
}

WATCardOffice::Job *WATCardOffice::requestWork()
{
    if (jobQueue.empty()){
        jobEmpty.wait();
    }
    Job * result = jobQueue.front();
    jobQueue.pop();
    return result;
}

void WATCardOffice::Courier::main(){
    for(;;){
        _Accept (~Courier){
            break;
        }
        Job* job = office->requestWork();
        office->bank.withdraw(job->sid, job->amount);   //withdraw from bank
        //job->result();                          //wait for the future watcard
        //job->result.deposit(job->amount);       //!!!update watcard
        bool failed = (mprng()%6 ==0);       //compute failure
        if (failed){
            _Resume Lost() ;        // !!!throw lost exception, into the future HOW??
        }
    }
}

void WATCardOffice::main(){
    Courier *couriers[numCouriers];
    for (int i = 0; i < numCouriers; i++){
        couriers[i] = new Courier(this);
    }  // create fix-sized couriers pool

    for (;;){
        _Accept(~WATCardOffice){        //accept descructor
            for (int i = 0; i < numCouriers;i++){   //kill couriers
                delete(couriers[i]);
            }
            break;  
        }
        or _Accept( create ){
            //callback for create
        }or _Accept( transfer ){
            //callback for transfer
        }
    }
    return; 
}



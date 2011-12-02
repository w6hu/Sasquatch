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
    return job->result;
}

FWATCard WATCardOffice::transfer( unsigned int sid, unsigned int amount, WATCard *card )
{
   // Job * job = new Job(sid, amount, card);
   // jobQueue.push(job);                         //!!!!insert new job to queue
   //  jobEmpty.signal();                          //wake up potential waiting requestWork
  //  return job->result;
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
        WATCard *card = new WATCard();
        card->deposit(job->amount);                          //wait for the future watcard
              //!!!update watcard
        bool failed = (mprng()%6 ==0);       //compute failure
        if (failed){
            job->result.exception(new WATCardOffice::Lost());     // !!!throw lost exception, into the future HOW??
        }else{
            job->result.delivery(card);
        }
    }
}

void WATCardOffice::main(){
    Courier *couriers[numCouriers];
    for (unsigned int i = 0; i < numCouriers; i++){
        couriers[i] = new Courier(this);
    }  // create fix-sized couriers pool

    for (;;){
        _Accept(~WATCardOffice){        //accept descructor
            for (unsigned int i = 0; i < numCouriers;i++){   //kill couriers
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



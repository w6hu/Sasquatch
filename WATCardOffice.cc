#include "WATCardOffice.h"
#include "MPRNG.h"

extern MPRNG mprng;                                                     //random number generate

WATCardOffice::WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers ) :
  prt(prt), bank(bank)
{
    this->numCouriers = numCouriers;                                    //constructor
}//WATCardOffice

FWATCard WATCardOffice::create( unsigned int sid, unsigned int amount, WATCard *&card )
{
    this->sid = sid;                                                    
    this->amount = amount;
    card = new WATCard();
    Job * job = new Job(sid, amount, card);                             //create new job
    jobQueue.push(job);                                                 //insert new job to queue
    return job->result;                                                 //return a future
}//create

FWATCard WATCardOffice::transfer( unsigned int sid, unsigned int amount, WATCard *card )
{
    this->sid = sid;
    this->amount = amount;
    Job * job = new Job(sid, amount, card);                             //create a new job
    jobQueue.push(job);                                                 //insert new job to queue
    return job->result;                                                 //return a future
}//transfer

WATCardOffice::Job *WATCardOffice::requestWork()
{
    if (jobQueue.empty()){
        return NULL;                                                    
    }//if
    Job * result = jobQueue.front();                                    //get job
    jobQueue.pop();
    return result;
}//requestWork

void WATCardOffice::Courier::main(){
    prt.print(Printer::Courier, id, 'S');
    for(;;){
        _Accept (~Courier){
            break;
        }else{
            Job* job = office->requestWork();
            if (job == NULL){
                break;
            }//if
            prt.print(Printer::Courier, id, 't', job->sid, job->amount );
            office->bank.withdraw(job->sid, job->amount);               //withdraw from bank
            job->card->deposit(job->amount);                            //wait for the future watcard
            bool failed = (mprng()% 6 ==0);                             //compute failure
            if (failed){
                job->result.exception(new  WATCardOffice::Lost());      // throw lost exception into the future 
            }else{
                job->result.delivery(job->card);                        //get the future ready
                prt.print(Printer::Courier, id, 'T', job->sid, job->amount );
            }//if
            delete job;
        }//_Accept
    }//for
    prt.print(Printer::Courier, id, 'F');
}//Courier::main

void WATCardOffice::main(){
    prt.print(Printer::WATCardOffice, 'S');                         
    Courier *couriers[numCouriers];                 
    for (unsigned int i = 0; i < numCouriers; i++){
        couriers[i] = new Courier(this, prt, i);                        //initialize courier
    }  // create fix-sized couriers pool

    for (;;){
        _Accept(~WATCardOffice){                                        //accept descructor
            for (unsigned int i = 0; i < numCouriers;i++){              //kill couriers
                _Accept (requestWork){                                  //accept so we can terminate
                }
            }//for
            for (unsigned int i = 0; i < numCouriers;i++){              //kill couriers
                delete(couriers[i]);                                    
            }//for
            break;  
        }or _When (!jobQueue.empty()) _Accept( requestWork){
            prt.print(Printer::WATCardOffice, 'W');
        }
        or _Accept( create ){
            prt.print(Printer::WATCardOffice, 'C', sid, amount);
            //callback for create

        }or _Accept( transfer ){
            //callback for transfer
            prt.print(Printer::WATCardOffice, 'T', sid, amount);
        }//_Accept
    }
    prt.print(Printer::WATCardOffice, 'F'); 
}//WATCardOffice::main



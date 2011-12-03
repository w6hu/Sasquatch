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
    this->sid = sid;
    this->amount = amount;
    card = new WATCard();
    Job * job = new Job(sid, amount, card);
    jobQueue.push(job);                         //insert new job to queue
    return job->result;
}

FWATCard WATCardOffice::transfer( unsigned int sid, unsigned int amount, WATCard *card )
{
    this->sid = sid;
    this->amount = amount;
    Job * job = new Job(sid, amount, card);
    jobQueue.push(job);                         //!!!!insert new job to queue
    return job->result;
}

WATCardOffice::Job *WATCardOffice::requestWork()
{
    if (jobQueue.empty()){
        return NULL;
    }
    Job * result = jobQueue.front();
    jobQueue.pop();
    return result;
}

void WATCardOffice::Courier::main(){
    prt.print(Printer::Courier, id, 'S');
    for(;;){
        _Accept (~Courier){
            break;
        }else{
            Job* job = office->requestWork();
            if (job == NULL){
                break;
            }
            prt.print(Printer::Courier, id, 't', job->sid, job->amount );
            office->bank.withdraw(job->sid, job->amount);   //withdraw from bank
            job->card->deposit(job->amount);                          //wait for the future watcard
            //!!!update watcard
            bool failed = (mprng()% 6 ==0);       //compute failure
            if (failed){
                job->result.exception(new  WATCardOffice::Lost());     // !!!throw lost exception into the future 
            }else{
                job->result.delivery(job->card);     //get the future ready
                prt.print(Printer::Courier, id, 'T', job->sid, job->amount );
            }
            delete job;
        }
    }
    prt.print(Printer::Courier, id, 'F');
}

void WATCardOffice::main(){
    prt.print(Printer::WATCardOffice, 'S');
    Courier *couriers[numCouriers];
    for (unsigned int i = 0; i < numCouriers; i++){
        couriers[i] = new Courier(this, prt, i);
    }  // create fix-sized couriers pool

    for (;;){
        _Accept(~WATCardOffice){        //accept descructor
            for (unsigned int i = 0; i < numCouriers;i++){   //kill couriers
                _Accept (requestWork){
                }
            }
            for (unsigned int i = 0; i < numCouriers;i++){   //kill couriers
                delete(couriers[i]);
            }
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
        }
    }
    prt.print(Printer::WATCardOffice, 'F'); 
}



#ifndef __MPRNG_H__
#define __MPRNG_H__

#include "PRNG.h"
#include <uC++.h>

_Monitor MPRNG: private PRNG{
    public:
        uint32_t seed(){
            return PRNG::seed();
        }
        void seed(uint32_t s){
            PRNG::seed(s);
        }
        uint32_t operator()(){
            return PRNG::operator()();
        }
        uint32_t operator()( uint32_t u){
            return PRNG::operator()(u);
        }
        uint32_t operator()(uint32_t l, uint32_t u){
            return PRNG::operator()(l, u);
        }
};

#endif

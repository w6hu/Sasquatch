#ifndef __MPRNG_H__
#define __MPRNG_H__

#include "PRNG.h"
#include <uC++.h>

_Monitor MPRNG: private PRNG{
    public:
        uint32_t seed();
        void seed(uint32_t s);
        uint32_t operator()();
        uint32_t operator()( uint32_t u);
        uint32_t operator()(uint32_t l, uint32_t u);
};

#endif

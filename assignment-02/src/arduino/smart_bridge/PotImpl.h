#ifndef __POTIMPL__
#define __POTIMPL__

#include "Pot.h"

class PotImpl: public Pot {

public:
    PotImpl(int pin);
    int getValue();

private:
    int pin;

};

#endif
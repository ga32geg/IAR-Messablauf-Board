#ifndef TIMER4_H
#define TIMER4_H

#include "ioCC1110.h"
#include "ioCCxx10_bitdef.h"


void McuWaitUs(unsigned short usec);
void McuWaitMs(unsigned short msec);
void McuWaitS(unsigned short sec);
void McuWaitMin(unsigned short min);

#endif
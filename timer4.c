#include "timer4.h"


#pragma optimize=none
void McuWaitUs(unsigned short usec)
{
    usec>>= 1;          // Divide by 2 to achieve better resolution

    while(usec > 1)     // compare: ~13 cycles 10 Stück
    {
        asm("NOP");     // 1 cycle/NOP
        asm("NOP");
        asm("NOP");
        asm("NOP");
        asm("NOP");
        asm("NOP");    
        asm("NOP");
        asm("NOP");
        asm("NOP");
        asm("NOP");
                         
        usec--;        // decr: ~7 cycles
    }
}

#pragma optimize=none
void McuWaitMs(unsigned short msec)
{
    while(msec--)
      McuWaitUs(1000);
}

#pragma optimize=none
void McuWaitS(unsigned short sec)
{
    while(sec--)
      McuWaitMs(1000);
}

#pragma optimize=none
void McuWaitMin(unsigned short min)
{
    while(min--)
      McuWaitMs(60);
}

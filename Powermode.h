#ifndef POWERMODE_H
#define POWERMODE_H

#include "ioCC1110.h"

// Global Variables:
extern unsigned char XtalCLK_Flag;

// Declarations:
void InitCLK();
//void InitRCOSC();
void setup_sleep_interrupt(void);
//void sleep();

#endif
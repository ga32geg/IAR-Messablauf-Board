#ifndef ADC_H
#define ADC_H

//extern float ADC_voltage;              // 16 Bit ADC-voltage
//extern float ADC_Offset; 


#include "ioCC1110.h"
#include "ioCCxx10_bitdef.h"
#include "Powermode.h"


int Initadc(); 
int readADC(); 


#endif
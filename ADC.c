#include "ADC.h" 
#include "ioCCxx10_bitdef.h"


int Initadc()
{
  /* Set system clock source to HS XOSC, with no pre-scaling.
   * Ref. [clk]=>[clk_xosc.c]
   */	
  SLEEP &= ~SLEEP_OSC_PD;
  while( !(SLEEP & SLEEP_XOSC_S) );
  CLKCON = (CLKCON & ~(CLKCON_CLKSPD | CLKCON_OSC)) | CLKSPD_DIV_1;
  while (CLKCON & CLKCON_OSC);
  SLEEP |= SLEEP_OSC_PD;

  /* I/O-Port configuration :
   * PIN0_7 is configured to an ADC input pin.  */
  // Set [ADCCFG.ADCCFG7 = 1].
  ADCCFG |= ADCCFG_7;  //;
  //ADCCFG |= 0x80; // Enable ADC function for P0_7 (Data Sheet S.96)

  /* ADC configuration :
   *  - [ADCCON1.ST] triggered
   *  - 12 bit resolution
   *  - Single-ended
   *  - Single-channel, due to only 1 pin is selected in the ADCCFG register
   *  - Reference voltage is VDD on AVDD pin

   *  Note: - [ADCCON1.ST] must always be written to 11
   *
   *  The ADC result is represented in two's complement.
   */

  // Set [ADCCON1.STSEL] according to ADC configuration */
  ADCCON1 = (ADCCON1 & ~ADCCON1_STSEL) | STSEL_ST | BIT1 | BIT0;
  //ADCCON1 = 0x33; 
  // Set [ADCCON2.SREF/SDIV/SCH] according to ADC configuration */
  ADCCON2 = ADCCON2_SREF_1_25V | ADCCON2_SDIV_512 | ADCCON2_SCH_AIN7;
  //ADCCON2 = 0x36;
return 0; 
}

int readADC()
{
  unsigned short adc_result;  //unint16_t
  int adc; 
	
 /* ADC conversion :
   * The ADC conversion is triggered by setting [ADCCON1.ST = 1].
   * The CPU will then poll [ADCCON1.EOC] until the conversion is completed.
   */ 
  /* Set [ADCCON1.ST] and await completion (ADCCON1.EOC = 1) */
  ADCCON1 |= ADCCON1_ST | BIT1 | BIT0;
  while( !(ADCCON1 & 0x80));

  /* Store the ADC result from the ADCH/L register to the adc_result variable.
   * The 4 LSBs in ADCL will not contain valid data, and are masked out.
   */	
  adc_result = ADCL ;//(ADCL & 0xF0); // & 0xF0= 1111 0000 also nur die 4 linken Bits 
  adc_result |= (ADCH <<8);  // Bitshift ADCH 8 bit nach rechts 
  adc_result >>= 4;
  adc = adc_result; 	// Shift 4 due to 12 bits resolution

  return adc; 
	
}
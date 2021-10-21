#include "Powermode.h"
//#include <intrins.h>



/* Init/Change to XTAL as System CLK

Input:  -
Output: -
*/
void InitCLK()
{
  SLEEP &= ~0x04;               // power up Oscillators
  while( !(SLEEP & 0x40) );     // wait until XTAL stable
  CLKCON = (CLKCON & ~(0x07 | 0x40)) | 0x00; // XTAL 26 MHz as System-CLK
  while (CLKCON & 0x40);
  SLEEP |= 0x04;
  
  XtalCLK_Flag = 1;             // set XTALCLK_Flag
	
 // P1_1=1; 
}

/* Init/Change to HS RCOSC as System CLK and set LS XOSC as CLK source
   for Sleep Timer.
Input:  -
Output: -
*/
/*
void InitRCOSC()
{
   // Switch system clock source to HS RCOSC and max CPU speed:
   // Note that this is critical for Power Mode 2. After reset or
   // exiting Power Mode 2 the system clock source is HS RCOSC,
   // but to emphasize the requirement we choose to be explicit here.
   SLEEP &= ~0x04;
   while( !(SLEEP & 0x20) );
   CLKCON = (CLKCON & ~0x07) | 0x40 | (0x01 << 3);
   while ( !(CLKCON & 0x40) ) ;
   SLEEP |= 0x04;
   
   // Set LS XOSC as the Sleep Timer clock source (CLKCON.OSC32 = 0)
   CLKCON &= ~0x80;
}
*/

/* Function which sets up the Sleep Timer Interrupt
*  for Power Mode 2 usage.
Input:  -
Output: -
*/
/*
void setup_sleep_interrupt(void)
{
    // Clear Sleep Timer CPU Interrupt flag (IRCON.STIF = 0)
    STIF = 0;

    // Clear Sleep Timer Module Interrupt Flag (WORIRQ.EVENT0_FLAG = 0)
    WORIRQ &= ~0x01;

    // Enable Sleep Timer Module Interrupt (WORIRQ.EVENT0_MASK = 1)
    WORIRQ |= 0x10;

    // Enable Sleep Timer CPU Interrupt (IEN0.STIE = 1)
    STIE = 1;

    // Enable Global Interrupt (IEN0.EA = 1)
    EA = 1;
}
*/


/***********************************************************************************
* @fn          sleep_timer_isr
*
* @brief       Sleep Timer Interrupt Service Routine, which executes when
*              the Sleep Timer expires. Note that the [SLEEP.MODE] bits must
*              be cleared inside this ISR in order to prevent unintentional
*              Power Mode 2 entry.
*
* @param       void
*
* @return      void
*/
/*
//#pragma vector = ST_VECTOR
//__interrupt void sleep_timer_isr(void)
void sleep_timer_isr(void) interrupt ST_VECTOR //veränderter Code 
{
    // Clear Sleep Timer CPU interrupt flag (IRCON.STIF = 0)
    STIF = 0;

    // Clear Sleep Timer Module Interrupt Flag (WORIRQ.EVENT0_FLAG = 0)
    WORIRQ &= ~0x01;

    // Clear the [SLEEP.MODE] bits, because an interrupt can also occur
    // before the SoC has actually entered Power Mode 2.
    SLEEP &= ~0x03;

    // Set SRF04EB LED1 to indicate Power Mode 2 exit
    P1_0 = 0;
}
*/

/* Changes Powermode to PM2

Input:  -
Output: -
*/
/*
// Enter power mode as described in chapter 13.1.3 in the datasheet. 
void sleep()
{
SLEEP = 0x06;  
	_nop_();
	_nop_();
	_nop_();
if( SLEEP & 0x03 ) {
DMAREQ = 0x01;
  _nop_();
 PCON |= 0x01;
_nop_(); }
}
*/

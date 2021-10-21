#include "Radio.h"
#include "Powermode.h"


/******************************************************************************
* important notice:
*
* In the function InitRadio():
* FREQ1 register is dependent on which device u use
* if(device==Evalboard): FREQ1 = 0x66
* if(device==self made one): FREQ1 = 0x65
*
* this is due the slight frequency offset of the two devices
******************************************************************************/


/* Initialize Radio
Input:  -
Output: -
*/
void InitRadio()
{
  // Set the system clock source to HS XOSC and max CPU speed,
  // ref. [clk]=>[clk_xosc.c]
  if(XtalCLK_Flag == 0)
    InitCLK();
  
  // Modulated = true 
  // Carrier frequency = 868.299866 
  // Sync word qualifier mode = 30/32 sync word bits detected 
  // Preamble count = 4 
  // Packet length mode = Variable packet length mode. Packet length configured by the first byte after sync word 
  // PA ramping = false 
  // Address config = No address check 
  // Channel number = 0 
  // Manchester enable = false 
  // CRC enable = true 
  // Whitening = false 
  // TX power = 0 
  // RX filter BW = 58.035714 
  // Data rate = 1.19948 
  // Packet length = 255 
  // Base frequency = 868.299866 
  // Channel spacing = 199.951172 
  // Modulation format = GFSK 
  // Device address = 0 
  // Deviation = 5.157471 
   
  
	//  Address Config = No address check 
//  Base Frequency = 868.299866 
//  CRC Enable = true 
//  Carrier Frequency = 868.299866 
//  Channel Number = 0 
//  Channel Spacing = 199.951172 
//  Data Rate = 1.19948 
//  Deviation = 5.157471 
//  Device Address = 0 
//  Manchester Enable = false 
//  Modulated = true 
//  Modulation Format = GFSK 
//  PA Ramping = false 
//  Packet Length = 255 
//  Packet Length Mode = Variable packet length mode. Packet length configured by the first byte after sync word 
//  Preamble Count = 4 
//  RX Filter BW = 58.035714 
//  Sync Word Qualifier Mode = 30/32 sync word bits detected 
//  TX Power = 0 
//  Whitening = false 

 PKTCTRL0  = 0x05      ; //  Packet Automation Control PKTCTRL0
 FSCTRL1   = 0x06      ; //  Frequency Synthesizer Control FSCTRL1
 FREQ2     = 0x21      ; //  Frequency Control Word, High Byte FREQ2
 FREQ1     = 0x65      ; //  Frequency Control Word, Middle Byte FREQ1
 FREQ0     = 0x6A      ; //  Frequency Control Word, Low Byte FREQ0
 //MDMCFG4   = 0xF5      ; //  Modem configuration MDMCFG4
 MDMCFG4   = 0xC5; // modem configuration für Evalboard
 MDMCFG3   = 0x83      ; //  Modem Configuration MDMCFG3
 MDMCFG2   = 0x13      ; //  Modem Configuration MDMCFG2
 DEVIATN   = 0x15      ; //  Modem Deviation Setting DEVIATN
 MCSM0     = 0x18      ; //  Main Radio Control State Machine Configuration MCSM0
 FOCCFG    = 0x17      ; //  Frequency Offset Compensation Configuration FOCCFG
 FSCAL3    = 0xE9      ; //  Frequency Synthesizer Calibration FSCAL3
 FSCAL2    = 0x2A      ; //  Frequency Synthesizer Calibration FSCAL2
 FSCAL1    = 0x00      ; //  Frequency Synthesizer Calibration FSCAL1
 FSCAL0    = 0x1F      ; //  Frequency Synthesizer Calibration FSCAL0
 PA_TABLE0 = 0x50      ; //  PA Power Setting 0 PA_TABLE0
 VERSION   = 0x04      ; //  Chip ID[7:0] VERSION
 //LQI       = 0x28      ; //  Demodulator Estimate for Link Quality LQI
 PKTLEN    = 10      ; //  Packet Length PKTLEN



 /* 
  PKTCTRL0  = 0x05; // packet automation control 
  FSCTRL1   = 0x06; // frequency synthesizer control 
  FREQ2     = 0x21; // frequency control word, high byte 
  FREQ1     = 0x65; // frequency control word, middle byte 
  FREQ0     = 0x6A; // frequency control word, low byte 
// MDMCFG4 = 0xF6 //modem configuration 
  MDMCFG4   = 0xC5; // modem configuration 
  MDMCFG3   = 0x83; // modem configuration 
  MDMCFG2   = 0x13; // modem configuration
  DEVIATN   = 0x15; // modem deviation setting 
  MCSM0     = 0x18; // main radio control state machine configuration 
  FOCCFG    = 0x17; // frequency offset compensation configuration 
  FSCAL3    = 0xE9; // frequency synthesizer calibration 
  FSCAL2    = 0x2A; // frequency synthesizer calibration 
  FSCAL1    = 0x00; // frequency synthesizer calibration 
  FSCAL0    = 0x1F; // frequency synthesizer calibration 
#define  TEST1     = 0x31; // various test settings 
#define  TEST0     = 0x09; // various test settings 
  PA_TABLE0 = 0x50; // pa power setting 0   
  PKTLEN = 10;  
	*/
  RFIF = 0;
  RFTXRXIF = 0;
  //////////////////
 // RFIF |= 0xC0;
  //EA = 1;
}


/* Transmit Data Packet
Input:  Data to transmit as pointer on array
        length of Data
Output:
Note: RFD register can not be written before issuing STX strobe
      (data sheet S.188)
*/
void transmit(unsigned char* TXdata, unsigned char length)
{
  unsigned char m; //Fehlermeldung! muss nicht unbedingt richtig sein
  RFST = RFST_STX;
  while(!RFTXRXIF); //Falls keine Daten im Register bereit sind warten 
  RFTXRXIF = 0;
  RFD = TXdata[0];   
  for ( m = 1; m < length ; m++)
  {
    while (!RFTXRXIF); // Problem Stelle 
    RFTXRXIF = 0;
    RFD = TXdata[m];
    P1_0 ^= 1; //Grüne LED blinkt beim Senden 
  }  
  while ((RFIF & 0x10) == 0); // Wait for IRQ_DONE
  RFIF &= ~0x10; //clear IRQ_Done Flag 
  RFTXRXIF = 0;
}


void receive()
{
  unsigned char j; 
  RFST = RFST_SRX;
  while(MARCSTATE!=MARC_STATE_RX)
  while (!RFTXRXIF)
 { 
    P1_1=1; // Programm macht erst weiter, wenn ein Signal angekommen ist solange Leuchtet die rote LED
    P1_1=0;}; 
    RFTXRXIF = 0;
    Rxdata[0] = RFD; // length
  for ( j= 1; j < Rxdata[0] +2  ; j++) 
  {
    while (!RFTXRXIF);
    RFTXRXIF = 0;
    Rxdata[j] = RFD;	
    P1_1 ^= 1; // rote LED blinkt beim empfangen 
  }
}


signed short convertRssiByte()
{
  signed char rssiComp = RSSI;
  
  // Convert RSSI value from 2's complement to decimal value.
  signed short rssiDec = (signed short) rssiComp;

  // Convert to absolute value (RSSI value from radio has resolution of
  // 0.5 dBm) and subtract the radio's appropriate RSSI offset.
  if(rssiDec < 128)
  {
      return (rssiDec/2) - RssiOffset;
  }
  else
  {
      return ((rssiDec - 256)/2) - RssiOffset;
  }
	
}

void Rx()
{
    RFmode = Mode_Rx;
    RFST=RFST_SIDLE;  
    while(MARCSTATE!=MARC_STATE_IDLE); 
    receive();	 
}

void Tx_process()
{
    RFmode = Mode_Tx;
    RFST=RFST_SIDLE;  
    while(MARCSTATE!=MARC_STATE_IDLE);
}	

#include "SelectRFInput.h"
#include "ioCCxx10_bitdef.h"
#include "Timer4.h" 



void SelDet()
{ //Switch Pfad RF1
  // GPIO P1_0, P1_1 as Output indem es Port zu 0 setzt 
	dir0 |=  (BIT0 | BIT1) ; //setzt P0_0 und P0_1 zu output
	P0INP |=  (BIT0 | BIT1) ; //Pull-up/Pull down mode
	// Change Switch to RF1 (Detector In)
	ControlSWA= 0; // P0_0
	ControlSWB= 1; // P1_1
	//Wait for End of Bouncing (max. 80ns)
        McuWaitMs(1); 
}

/* Select RF-uC-way 
Input:  -
Output: -
*/
void SeluC()
{ //Switch Pfad RF2
  // GPIO P1_0, P1_1 as Output indem es Port zu 0 setzt 
  dir0 |= (BIT0 | BIT1) ; //setzt P0_0 und P0_1 zu output
  P0INP |= (BIT0 | BIT1) ; //Pull-up/Pull down mode

  // Change Switch to RF2 (uController In)
  ControlSWA= 1;
  ControlSWB= 0;

 // Wait for End of Bouncing (max. 80ns)
  McuWaitMs(1); 
}

/* Select Attenuation 15 dB
Input:  -
Output: -
*/

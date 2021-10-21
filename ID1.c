#include "ID.h"
#include "ioCC1110.h"
#include "ioCCxx10_bitdef.h"



/* Set ID-number of the device
Input:  Desired Id as one Byte 
Output: -
*/
//void getIDx(unsigned char id)
void getIDx()
{
unsigned char idx; 
//Bits f�r P1_2 und P1_3 zu 0 setzen um als IO und als Input zu konfigurieren
P1SEL &= ~ (BIT3 | BIT2) ; //setzt P1_2 und P1_3 zu IO Ports auch alle zu 0 setzen f�r 
P1DIR &= ~ (BIT3 | BIT2) ; //setzt P1_2 und P1_3 zu INPUT Bits m�ssen 0 sein f�r Input
P0INP &= ~ (BIT3 | BIT2) ; //Input Mode pull/upp down 
idx = P1_3; 

}
#include "ID.h"
#include "Definitions.h"
#include "ioCC1110.h"
#include "ioCCxx10_bitdef.h"




/* Set ID-number of the device
Input:  Desired Id as one Byte 
Output: -
*/
//unsigned char getIDx(unsigned char idx)
/*
unsigned char IDx(unsigned char ID)
{
unsigned char idx; 	
//Bits für P1_2 und P1_3 zu 0 setzen um als IO und als Input zu konfigurieren
P1SEL &= ~ (BIT3 | BIT2) ; //setzt P1_2 und P1_3 zu IO Ports auch alle zu 0 setzen für 
P1DIR &= ~ (BIT3 | BIT2) ; //setzt P1_2 und P1_3 zu INPUT Bits müssen 0 sein für Input

P1INP &= ~ (BIT3 | BIT2) ; //Input Mode pull/upp down 
P2INP |= BIT6 ; //Pull down an P1_2 und P1_3 noch mal nachfragen Bit 5 für alle Pins an Port 0 zu pull down
idx = D4; 
	return ID; 

}
*/
unsigned char getID()
{
unsigned char B0 = 0 ; // P1_7
unsigned char B1 = 0; // P1_6
unsigned char B2 = 0; // P1_5
unsigned char B3 = 0; // P1_4
unsigned char B4 = 0; // P1_3
unsigned char B5 = 0; // P1_2

unsigned char a =0; 
unsigned char b =0; 
unsigned char c =0;
unsigned char d =0; 
unsigned char e =0;
unsigned char f =0; 
	


P1SEL &= ~ (BIT2 | BIT3 | BIT4 | BIT5 |BIT6 |BIT7 ) ; //setzt P1_2 und P1_3 zu IO Ports auch alle zu 0 setzen für 
P1DIR &= ~ (BIT2 | BIT3 | BIT4 | BIT5 |BIT6 |BIT7 ) ; //setzt P1_2 und P1_3 zu INPUT Bits müssen 0 sein für Input
P1INP &= ~ (BIT2 | BIT3 | BIT4 | BIT5 |BIT6 |BIT7 ) ; //Input Mode pull/upp down 
P2INP |= BIT6 ; //Pull down an P1_2 und P1_3 pull down für alle GPIO an Port 1 mit Bit6 S.98 für alle Pins an Port 0 zu pull down
//P2INP &= ~ BIT6 ;
a |= D0;	
B0 |= a; // Bit 0

b |= P1_6;	
B1 |= ( b << 1 );
	
c |= D2;	
B2 |= ( c << 2 );

d |= D3;	
B3 |= ( d << 3 );

e |= D4;	
B4 |= ( e << 4 ); 

f |= D5;	
B5 |= ( f << 5 );
//ADCH << 8);  // Bitshift ADCH 8 bit nach rechts 

	
ID |= (B0 | B1 | B2 | B3 | B4 | B5); 

P2INP &= ~ BIT6 ; //Pull up wieder zurück zu VDD

return ID;


}
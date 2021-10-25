#include "ioCC1110.h"
#include "ioCCxx10_bitdef.h"
#include "Powermode.h"
#include "Radio.h"
#include "ID.h"
#include "SelectRFInput.h"
#include "Definitions.h"
#include "ADC.h"
#include "Timer4.h"


unsigned char pktRxFlag;
unsigned char pktTxFlag;
unsigned char RFmode;                  
unsigned char Rxdata[10];               
unsigned char Txdata[10];
signed short rssim[10];			
signed short rss[20];								
unsigned char length =10; 
unsigned char XtalCLK_Flag = 0;
unsigned char ID;
unsigned char IDB; 
double mean;
const signed short RssiOffset = 73;

// Definitions 
// DIP Ports

#define D5              P1_2
#define D4              P1_3
#define D3              P1_4
#define D2              P1_5
#define D1              P1_6
#define D0              P1_7
#define led1		P1_0 // green
#define led2            P1_1 // red
#define dir             P1DIR // input/output config of Pin1 (0/1)



int main(void)
{
unsigned char i, j, t, p;  
unsigned char n, z;  
int sumrssi;
int sumrssi2;
long int x, y, w; 
int mean0; 
unsigned char A; 
double mean2; 
signed short rssi;                      // rssi-value variable in dBm (!)
p=0; j=0, n=0, z=0; 	
length=10;	
// GPIO P1_0, P1_1 as Output indem Bit zu 1 gesetzt werden um die LED steuern zu können 
dir |=  (BIT0 | BIT1) ; //setzt P1_1 und P0_0 zu output	
led1=0; //LED ausschalten ansosten wären sie durch das auswählen des Ports automatisch eingeschaltet
led2=0;
InitCLK();

for(i=0;  i<2; i++)
{
  McuWaitS(1);
  led1=1; 
  led2=1; 
  McuWaitS(1);
  led1=0; 
  led2=0;  
}

    while(1)
    {   // Anweisungen Empfangen
	IDB = getID(); //Abfragen Board ID
        
        SeluC(); // Pfad auf uController Schalten
        //delay(1);
        InitCLK();
	InitRadio(); 
	length=10;
        Initadc(); 
        mean= readADC(); 
	Rx(); 
        
	z = Rxdata[4];//Zeitsteuerung
	n = Rxdata[3];//n: Anzahl der RSSI Durchläufe 	
        /*
	Rxdata[0]= 10; 
	Rxdata[2]=22; // Programm auswählen 
	Rxdata[3]=200; //Anzahl der RSSI Durchläufe
	n=Rxdata[3]; 
	*/
        
        
        if (Rxdata[1]==IDB)
        {
		
          if(Rxdata[2] == 22) //M für Mittelwert
          {	
            SelDet();
            Initadc();
            McuWaitS(3); 
            //Messung Detektor 
            t=n/10; 
            for(p=0; p<t; p++)
            {								
              for(j=0; j<10; j++)
              {	
                led1=1 ;							 
                rssi = readADC();
                rssim[j]=rssi; 
                led1=0; 
              }						
              //Mittelwert 10 Messungen 
              sumrssi=0; 
              mean0=0; 
              i=0; 
              for (i = 0; i < 10 ; i++)  //n Anzahl der rssi Messungen vorgegeben durch Python 
              {    
                      sumrssi= sumrssi+ rssim[i];  //Summe von rssim berechnen 
              }				
              mean0 = sumrssi/10;
              rss[p]=mean0; 				
            }			
            //Mittelwert über alle Itterationen
            sumrssi2=0; 
            mean=0; 
            for (i = 0; i < t ; i++)  //t=n/10; 
              {    
                sumrssi2= sumrssi2 + rss[i];  //Summe von rssim berechnen 
              }				
            //mean = (double) sumrssi2/t ;
            mean = sumrssi2/t ;
            mean =(1.25/2047)*mean;
            mean2= mean*100; 
            w =  mean*100; 
            x =  mean * 10000;
            y =  mean * 1000000; 
            mean = mean * 1000;                    
            mean = (mean/17.2) ;                        
            A = (unsigned char) mean2;
            w = A; 
            x = x - A*100; 
            y = y - x*100 - w*10000; 
            length =10; 
            Txdata[0] = length;
            Txdata[1] = length; 
            Txdata[2] = IDB;   
            Txdata[3] = (unsigned char) mean; 
            Txdata[4] = ( unsigned char ) A;
            Txdata[5] = (unsigned char)x; 
            Txdata[6] = (unsigned char)y; 
            SeluC(); // Pfad auf uController Schalten             
            //delay(1); 
            
            McuWaitS(z+10); 
            Tx_process(); 
            transmit(Txdata, length);                        
          }	
          
         if(Rxdata[2]== 33 ) //'R') //'R' Rssi
         {	
          SeluC();
          McuWaitS(z); 
          InitCLK();
          InitRadio();	
   
          //	Rx();	//Receive
          led1=0; 
          rssi = convertRssiByte();				 
   
          for (i = 1; i <= length ; i++)  
          { 
            Txdata[i] = 0;	
          } 
                  
          Txdata[0] = length;   //Txdata[0] = length; 
          Txdata[1] = IDB;   //ID =2
                  
          if(rssi<=0)
          {
            Txdata[2]=( unsigned char ) -rssi; 
            Txdata[3]=1; // ändern zu dem in Python
          }
            else
            {
              Txdata[2]= (unsigned char) rssi;
              Txdata[5]= 0 ; //ändern zu dem in Python 
            }									
                           //Sendet Daten
          McuWaitS(z); 
          for (i = 1; i <= 2 ; i++)   
          {
              Tx_process(); 
              transmit(Txdata, length);
          }	
          SelDet(); 
          }	
         if( Rxdata[2]== 44) //'P')  //'P' Ping oder 44
          {
            SeluC();
            led2=1; //rote LED leuchtet 
            //Sendet Daten
            for (i = 1; i <= length ; i++)  
            { 
              Txdata[i] = 0;	
            }		
            InitCLK();
            InitRadio();  
    
            Txdata[0] = length;   
            Txdata[1] = IDB;   
            Tx_process(); 
            transmit(Txdata, length);							
            SelDet(); 

            led2=0;
            led1=0; 
           }
                  
         }
    }
}
 	 


/*
 * File:   main.c
 * Author: Mhmod Tayel
 *
 * Created on 23 October 2019, 17:26
 */


#include <xc.h>
#include <stdint.h>
#include "config.h"
#define _XTAL_FREQ 4000000
#define Baud 9600
//--------------------------
// IO Pins Defines
#define UP RD5
#define Down RD6
#define Send RD7

//--------------------------
// Functions Declarations
void UART_TX_Init(void);
void UART_Write(uint8_t);
//--------------------------
void main(void) {
    UART_TX_Init();
     uint8_t Data = 0;
     unsigned char segment_code[10] = {0xFC,0x60,0xDA,0xF2,0x66,0xB6,0xBE,0xE0,0xFE,0xF6};
     TRISB = 0x00;
    PORTB = 0x00;
     TRISD = 1;
     PORTD = 0;
     
     
    while(1){
        if (Data > 9){
            Data=0;
        }
     if (UP) // Increment The Data Value
    {
      Data++;
      __delay_ms(500);
    } 
    if (Down) // Decrement The Data Value
    {
      Data--;
      __delay_ms(500);
    }
    if (Send) // Send The Current Data Value Via UART
    {
      UART_Write(Data);
      __delay_ms(500);
    }
    PORTB= segment_code[Data]; // Display The Current Data Value @ PORTD
    }
    
    
    return;
}

void UART_TX_Init(void){
    BRGH=1;  // Set For High-Speed Baud Rate
    
   //  Set The Baud Rate To Be 9600 bps
    SPBRG  =25;//(_XTAL_FREQ-Baud*16)/(Baud*16); 
    
// Enable The Ascynchronous Serial Port
    SYNC =0;
    SPEN =1;

// Set The RX-TX Pins to be in UART mode
    TRISC6 = 1;  
    TRISC7 = 1;  
    TXEN = 1; // Enable UART Transmission
}
void UART_Write(uint8_t data)
{
  while(!TRMT);
  TXREG = data;
}

    
    
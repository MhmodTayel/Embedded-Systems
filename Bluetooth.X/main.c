/*
 * File:   main.c
 * Author: Mhmod Tayel
 *
 * Created on 23 October 2019, 21:51
 */


#include <xc.h>
#include <stdint.h>
#include "config.h"
#define _XTAL_FREQ 4000000
#define Relay_ON 49
#define Relay_OFF 50

void UART_RX_Init(void);
uint8_t UART_Buffer =0;

void main(void) {
    UART_RX_Init();
    TRISB0 =0;
    RB0 =0;
    while(1){
        // Nothing to do here , All the work in interrupt
    }
    return;
}

void UART_RX_Init(){
   BRGH = 1; // Set For High-Speed Baud Rate
   SPBRG = 25; // Set The Baud Rate To Be 9600 bps
    // Enable The Ascynchronous Serial Port
   SYNC = 0;
   SPEN = 1;
     // Set The RX-TX Pins to be in UART mode (not io)
  TRISC6 = 1; // As stated in the datasheet
  TRISC7 = 1; // As stated in the datasheet
   //--[ Enable UART Receiving Interrupts ]--
  RCIE = 1; // UART Receving Interrupt Enable Bit
  PEIE = 1; // Peripherals Interrupt Enable Bit
  GIE = 1; // Global Interrupt Enable Bit
  //------------------
  CREN = 1; // Enable Data Continous Reception
}

void __interrupt () ISR (void) {
     if (RCIF == 1) {
    UART_Buffer = RCREG; // Read The Received Data Buffer 
    // This could have been done within the main loop. Since it's not
    // Excessive processing, so it's OK to do it here below
    if(UART_Buffer == Relay_ON)
        RB0=1;
    if(UART_Buffer == Relay_OFF)
        RB0=0;
    RCIF = 0;
}
}
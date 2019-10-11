/*
 * File:   main.c
 * Author: Mhmod Tayel.
 *
 * Created on 09 October 2019, 19:33
 */
// unsigned char segment_code[10] = {0xFC,0x60,0xDA,0xF2,0x66,0xB6,0xBE,0xE0,0xFE,0xF6};

#include <xc.h>
#include "config.h"
#define _XTAL_FREQ 4000000
void main(void) {
     unsigned char segment_code[10] = {0xF6,0xFE,0xE0,0xBE,0xB6,0x66,0xF2,0xDA,0x60,0xFC};
      
    unsigned char counter=0;
    TRISB = 0x00;
    PORTB = 0x00;
    TRISC = 0x00;
    PORTC = 0x00;
     
    while(1){
        for(counter;counter<=9;counter++){
            PORTCbits.RC1=1;
          PORTB = segment_code[counter];
          __delay_ms(1000);
          
        }
        counter=0;
        PORTCbits.RC1=0;
          for(counter;counter<=9;counter++){
            PORTCbits.RC2=1;
          PORTB = segment_code[counter];
          __delay_ms(1000);
          
        }
         counter=0;
        PORTCbits.RC2=0;
          for(counter;counter<=9;counter++){
            PORTCbits.RC3=1;
          PORTB = segment_code[counter];
          __delay_ms(1000);
          
        }
          counter=0;
        PORTCbits.RC3=0;
          for(counter;counter<=9;counter++){
            PORTCbits.RC2=1;
          PORTB = segment_code[counter];
          __delay_ms(1000);
   
        }
         counter=0;
        PORTCbits.RC2=0;
    }
    return;
}
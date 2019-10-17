/*
 * File:   main.c
 * Author: Mhmod Tayel
 *
 * Created on 17 October 2019, 15:05
 */


#include <xc.h>
#include "config.h"
#define _XTAL_FREQ 4000000
float calc_dist(void);
void main(void) {
    unsigned char dist =0;
    TRISB = 0;
    PORTB = 0;
    TRISC2 = 0;
    TRISC3 = 1;
    T1CKPS0 = 0;  // clear the pre-scaler select bits
    T1CKPS1 = 0;  // .........
    TMR1CS = 0;  //clock source as  timer mode 
    while(1){
             dist = calc_dist() ;
        if(dist <= 10){
             PORTBbits.RB0=1;
        } 
        else if (dist > 10 && dist <=15){
            PORTBbits.RB0=0;
            PORTBbits.RB1=1;
        } else if (dist > 15){
            PORTBbits.RB1=0;
            PORTBbits.RB2=1;
          
        }else{
             PORTB=0;
        }
    }
       /* dist = calc_dist()/5 ;
          switch(dist){
            case 1:
             PORTBbits.RB0=1; break;
            case 2:
                PORTBbits.RB0=0;
                PORTBbits.RB1=1; break;
            case 3:
                PORTBbits.RB1=0;
                PORTBbits.RB2=1;
                PORTBbits.RB3=1; break;
            default :
                PORTB=0;
        }
        */
    
    return;
}
float calc_dist(void) {
    float distance = 0;
    TMR1=0; 
    // send trigger pulse
    RC2=1;
    __delay_us(10);
    RC2=0;
    // wait for echo pulse
    while(!RC3);
    TMR1ON=1;
    while(RC3);
    TMR1ON=0;
    distance = TMR1/58.82;
    return distance;
}
/*
 * File:   main.c
 * Author: Mhmod Tayel
 *
 * Created on 28 October 2019, 01:58
 */
 
#include <xc.h>
#include <stdint.h>
#include "config.h"
#define _XTAL_FREQ 4000000
void UART_RX_Init(void);
uint8_t UART_Buffer =0;
//--[ Pin Definitions ]--
#define OFF 48   // OFF 
#define ON 49   // ON with 0% Speed 
#define LV1 50   // 50% Speed 
#define LV2 51    // 75% Speed 
#define LV3 52  // 100% Speed 
#define Rev 53   // Reverse Direction 
//===============================
//--[ Function Declarations ]--
void PWM1_Set_Duty(uint16_t);
 
void main(void)
{
    UART_RX_Init();
  //--[ Configuration For IO Pins ]--

  // Set The Direction To Be Output Pins
  TRISD0 = 0;
  TRISD1 = 0;
  // Initially (0, 1) Say it's ClockWise rotation!
  // For Reversing The Direction Write (1, 0)
  RD0 = 0;
  RD1 = 0;
 
  //--[ Configure The CCP Module For PWM Mode ]--
  CCP1M3 = 1;
  CCP1M2 = 1;
  TRISC2 = 0; // The CCP1 Output Pin (PWM)
  // Set The PWM Frequency (2kHz)
  PR2 = 124;
  // Set The PS For Timer2 (1:4 Ratio)
  T2CKPS0 = 1;
  T2CKPS1 = 0;
  // Start CCP1 PWM !
  TMR2ON = 1;
 
  // The Main Loop (Routine)
  while(1)
  {
      if(UART_Buffer == OFF)
    {
      RD0 = 0;
      RD1 =0 ;
    }
      if(UART_Buffer == ON)
    {
      PWM1_Set_Duty(0);
      RD0 = 0;
      RD1 = 1;
    }
      if(UART_Buffer == LV1) // 50% DC
    {
      PWM1_Set_Duty(250);
    }
    if(UART_Buffer == LV2) // 75% DC
    {
      PWM1_Set_Duty(375);
    }
    if (UART_Buffer == LV3) // 100% DC
    {
      PWM1_Set_Duty(500);
    }
    if(UART_Buffer == Rev) // Reverse The Direction
    {
      RD0 = ~RD0;
      RD1 = ~RD1;
      UART_Buffer = LV1 ;
    }
    __delay_ms(10);  // Wait To Reduce The Simulation Overloading
  }
  return;
}
 
// Definition For PWM1_Set_Duty Function
void PWM1_Set_Duty(uint16_t DC)
{
  // Check The DC Value To Make Sure it's Within 10-Bit Range
  if(DC<1024)
  {
    CCP1Y = DC & 1;
    CCP1X = DC & 2;
    CCPR1L = DC >> 2;
  }
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
    RCIF = 0;
}
}

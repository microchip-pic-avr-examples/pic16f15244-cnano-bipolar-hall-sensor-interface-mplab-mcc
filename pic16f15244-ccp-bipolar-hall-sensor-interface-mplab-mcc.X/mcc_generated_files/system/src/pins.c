/**
 * Generated Driver File
 * 
 * @file pins.c
 * 
 * @ingroup  pinsdriver
 * 
 * @brief This is generated driver implementation for pins. 
 *        This file provides implementations for pin APIs for all pins selected in the GUI.
 *
 * @version Driver Version 3.0.0
*/

/*
� [2022] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/

#include "../pins.h"

void (*RB4_InterruptHandler)(void);
void (*RC2_InterruptHandler)(void);

void PIN_MANAGER_Initialize(void)
{
   /**
    LATx registers
    */
    LATA = 0x0;
    LATB = 0x0;
    LATC = 0x0;

    /**
    TRISx registers
    */
    TRISA = 0x3B;
    TRISB = 0xB0;
    TRISC = 0x76;

    /**
    ANSELx registers
    */
    ANSELA = 0x33;
    ANSELB = 0xE0;
    ANSELC = 0x78;

    /**
    WPUx registers
    */
    WPUA = 0x0;
    WPUB = 0x0;
    WPUC = 0x4;
  

    /**
    APFCONx registers
    */

    /**
    ODx registers
    */
   
    ODCONA = 0x0;
    ODCONB = 0x0;
    ODCONC = 0x0;
    /**
    SLRCONx registers
    */
    SLRCONA = 0x37;
    SLRCONB = 0xF0;
    SLRCONC = 0xFF;
    /**
    INLVLx registers
    */
    INLVLA = 0x3F;
    INLVLB = 0xF0;
    INLVLC = 0xFF;

    /**
    PPS registers
    */
    CCP1PPS = 0xC; //RB4->CCP1:CCP1;
    RX1PPS = 0x11; //RC1->EUSART1:RX1;
    RC3PPS = 0x03;  //RC3->PWM3:PWM3OUT;
    RC0PPS = 0x05;  //RC0->EUSART1:TX1;
    RB6PPS = 0x09;  //RB6->TMR0:TMR0;

   /**
    IOCx registers 
    */
    IOCAP = 0x0;
    IOCAN = 0x0;
    IOCAF = 0x0;
    IOCBP = 0x10;
    IOCBN = 0x0;
    IOCBF = 0x0;
    IOCCP = 0x4;
    IOCCN = 0x0;
    IOCCF = 0x0;

    RB4_SetInterruptHandler(RB4_DefaultInterruptHandler);
    RC2_SetInterruptHandler(RC2_DefaultInterruptHandler);

    // Enable PIE0bits.IOCIE interrupt 
    PIE0bits.IOCIE = 1; 
}
  
void PIN_MANAGER_IOC(void)
{
    // interrupt on change for pin RB4}
    if(IOCBFbits.IOCBF4 == 1)
    {
        RB4_ISR();  
    }
    // interrupt on change for pin RC2}
    if(IOCCFbits.IOCCF2 == 1)
    {
        RC2_ISR();  
    }
}
   
/**
   RB4 Interrupt Service Routine
*/
void RB4_ISR(void) {

    // Add custom IOCBF4 code

    // Call the interrupt handler for the callback registered at runtime
    if(RB4_InterruptHandler)
    {
        RB4_InterruptHandler();
    }
    IOCBFbits.IOCBF4 = 0;
}

/**
  Allows selecting an interrupt handler for IOCBF4 at application runtime
*/
void RB4_SetInterruptHandler(void (* InterruptHandler)(void)){
    RB4_InterruptHandler = InterruptHandler;
}

/**
  Default interrupt handler for IOCBF4
*/
void RB4_DefaultInterruptHandler(void){
    // add your RB4 interrupt custom code
    // or set custom function using RB4_SetInterruptHandler()
}
   
/**
   RC2 Interrupt Service Routine
*/
void RC2_ISR(void) {

    // Add custom IOCCF2 code

    // Call the interrupt handler for the callback registered at runtime
    if(RC2_InterruptHandler)
    {
        RC2_InterruptHandler();
    }
    IOCCFbits.IOCCF2 = 0;
}

/**
  Allows selecting an interrupt handler for IOCCF2 at application runtime
*/
void RC2_SetInterruptHandler(void (* InterruptHandler)(void)){
    RC2_InterruptHandler = InterruptHandler;
}

/**
  Default interrupt handler for IOCCF2
*/
void RC2_DefaultInterruptHandler(void){
    // add your RC2 interrupt custom code
    // or set custom function using RC2_SetInterruptHandler()
}
/**
 End of File
*/
 /**
   PWM3 Generated Driver API Header File
 
   @Company
     Microchip Technology Inc. 

   @File Name
    pwm3.h

   @Summary
     This is the generated header file for the PWM3 driver.
 
   @Description
     This header file provides APIs for the PWM3 driver.
     Generation Information :
         Driver Version    :  2.01
     The generated drivers are tested against the following:
         Compiler          :  XC8 v2.20
         MPLAB             :  MPLABX v5.40
 */

/*
© [2022] Microchip Technology Inc. and its subsidiaries.

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

#ifndef PWM3_H
 #define PWM3_H
 
 /**
   Section: Included Files
 */

 #include <xc.h>
 #include <stdint.h>

 /**
   Section: Macro Declarations
 */

 #define PWM3_INITIALIZE_DUTY_VALUE    0

 /**
   Section: PWM Module APIs
 */

 /**
   @Summary
     Initializes the PWM3

   @Description
     This routine initializes the PWM3_Initialize
     This routine must be called before any other PWM3 routine is called.
     This routine should only be called once during system initialization.

   @Preconditions
     None

   @Param
     None

   @Returns
     None

   @Comment
     

  @Example
     <code>
     uint16_t dutycycle;

     PWM3_Initialize();
     PWM3_LoadDutyValue(dutycycle);
     </code>
  */
 void PWM3_Initialize(void);

 /**
   @Summary
     Loads 16-bit duty cycle.

   @Description
     This routine loads the 16 bit duty cycle value.

   @Preconditions
     PWM3_Initialize() function should have been called 
         before calling this function.

   @Param
     Pass 16bit duty cycle value.

   @Returns
     None

   @Example
     <code>
     uint16_t dutycycle;

     PWM3_Initialize();
     PWM3_LoadDutyValue(dutycycle);
     </code>
 */
 void PWM3_LoadDutyValue(uint16_t dutyValue);
 
 #endif	//PWM3_H

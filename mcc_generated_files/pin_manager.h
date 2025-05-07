/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.7
        Device            :  PIC12F1822
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.31 and above
        MPLAB 	          :  MPLAB X 5.45	
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

/**
  Section: Included Files
*/

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set LED aliases
#define LED_TRIS                 TRISAbits.TRISA2
#define LED_LAT                  LATAbits.LATA2
#define LED_PORT                 PORTAbits.RA2
#define LED_WPU                  WPUAbits.WPUA2
#define LED_ANS                  ANSELAbits.ANSA2
#define LED_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define LED_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define LED_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define LED_GetValue()           PORTAbits.RA2
#define LED_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define LED_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define LED_SetPullup()          do { WPUAbits.WPUA2 = 1; } while(0)
#define LED_ResetPullup()        do { WPUAbits.WPUA2 = 0; } while(0)
#define LED_SetAnalogMode()      do { ANSELAbits.ANSA2 = 1; } while(0)
#define LED_SetDigitalMode()     do { ANSELAbits.ANSA2 = 0; } while(0)

// get/set SW aliases
#define SW_TRIS                 TRISAbits.TRISA4
#define SW_LAT                  LATAbits.LATA4
#define SW_PORT                 PORTAbits.RA4
#define SW_WPU                  WPUAbits.WPUA4
#define SW_ANS                  ANSELAbits.ANSA4
#define SW_SetHigh()            do { LATAbits.LATA4 = 1; } while(0)
#define SW_SetLow()             do { LATAbits.LATA4 = 0; } while(0)
#define SW_Toggle()             do { LATAbits.LATA4 = ~LATAbits.LATA4; } while(0)
#define SW_GetValue()           PORTAbits.RA4
#define SW_SetDigitalInput()    do { TRISAbits.TRISA4 = 1; } while(0)
#define SW_SetDigitalOutput()   do { TRISAbits.TRISA4 = 0; } while(0)
#define SW_SetPullup()          do { WPUAbits.WPUA4 = 1; } while(0)
#define SW_ResetPullup()        do { WPUAbits.WPUA4 = 0; } while(0)
#define SW_SetAnalogMode()      do { ANSELAbits.ANSA4 = 1; } while(0)
#define SW_SetDigitalMode()     do { ANSELAbits.ANSA4 = 0; } while(0)

// get/set BUZZER aliases
#define BUZZER_TRIS                 TRISAbits.TRISA5
#define BUZZER_LAT                  LATAbits.LATA5
#define BUZZER_PORT                 PORTAbits.RA5
#define BUZZER_WPU                  WPUAbits.WPUA5
#define BUZZER_SetHigh()            do { LATAbits.LATA5 = 1; } while(0)
#define BUZZER_SetLow()             do { LATAbits.LATA5 = 0; } while(0)
#define BUZZER_Toggle()             do { LATAbits.LATA5 = ~LATAbits.LATA5; } while(0)
#define BUZZER_GetValue()           PORTAbits.RA5
#define BUZZER_SetDigitalInput()    do { TRISAbits.TRISA5 = 1; } while(0)
#define BUZZER_SetDigitalOutput()   do { TRISAbits.TRISA5 = 0; } while(0)
#define BUZZER_SetPullup()          do { WPUAbits.WPUA5 = 1; } while(0)
#define BUZZER_ResetPullup()        do { WPUAbits.WPUA5 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/
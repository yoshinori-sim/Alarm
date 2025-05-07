/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.7
        Device            :  PIC12F1822
        Driver Version    :  2.00
*/

/*
 * PIC12F1822    Pickit
 * 1 VDD		 2      VDD
 * 2 RA5                BUZZER [Low active]
 * 3 RA4                Reed Switch (WPU) [Door close is Low] 
 * 4 RA3/MCLR    1      MCLR
 * 5 RA2                LED
 * 6 RA1/ICSPCLK 5      ICSP
 * 7 RA0/ICSPDAT 4      ICSP
 * 8 VSS         3      VSS
 *
 */


#include <xc.h>
#include <stdio.h>
//#include <stdbool.h>
#include "mcc_generated_files/mcc.h"

#define	WDT_Enable()   (WDTCONbits.SWDTEN = 1)
#define	WDT_Disable()  (WDTCONbits.SWDTEN = 0)

#define BUZZER_OFF()    BUZZER_SetHigh()
#define BUZZER_ON()     BUZZER_SetLow()

#define FVR_DISABLE()   (FVRCONbits.FVREN = 0)
#define FVR_ENABLE()    (FVRCONbits.FVREN = 1)
#define FVR_ISREADY()   (FVRCONbits.FVRRDY == 1)

#define ADC_ENABLE()    (ADCON0bits.ADON = 1)
#define ADC_DISABLE()   (ADCON0bits.ADON = 0)

#define LED_ON()        LED_SetHigh();
#define LED_OFF()       LED_SetLow();

#define ISOPEN()    SW_GetValue()


typedef enum
{
    st_Start,
    st_Idle,
    st_Monitor,
    st_WarBeep,
    st_WarSilent,
} _AlarmState;

typedef struct {
    uint16_t ElapsedTime;       ///< 経過時間 N * Ticktime
    uint8_t Lenght;             ///< 発音長   N * Ticktime
    uint8_t Period;             ///< 発音周期 N * Ticktime
    uint8_t Count;              ///< 発音回数 N * Ticktime
} _SoundTable;

_SoundTable soundTable[] = {
    {   0, 1, 2,  1 },  //  0 sec   1 times
    { 188, 4, 8,  5 },  // 30 sec   5 times
    { 375, 4, 8, 10 },  // 60 sec  10 times
    { 750, 4, 8, 20 },  // 120 sec 20 times
    {1125, 4, 8, 30 },  // 180 sec 30 times
};

uint8_t check_vdd( uint16_t adValue )
{
    if(adValue > 1904 )         // 2.2V相当以下 = 放電限度 （ Ni-MHのサイクル寿命を考慮して高めで終えている )
    {   // 周辺モジュールを可能な限り止めて永眠する
        BUZZER_OFF();
        LED_OFF();
        SW_ResetPullup();
        SW_SetDigitalOutput();
        SW_SetLow();    // リードスイッチのポートをLow出力として省エネ
        SLEEP();        // 復帰条件なしで永久にsleepしたままとする。
    }
    else if( adValue > 1744 )   // 2.4V相当以下 = 電池電圧低下警告
    {
        return 1;
    }
    return 0;
}

/*
    Main application
 */
void main(void)
{
    _AlarmState state = st_Start;
const _SoundTable initTable  = { 0, 0, 0, 0};
    _SoundTable currentCount = initTable;
//    bool flagBuzzer = false;
    uint8_t currentNumber = 0;
    adc_result_t adValue[4];
    uint8_t    adcnt = 0;
    

    // initialize the device
    SYSTEM_Initialize();

    // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
    // Use the following macros to:

    // Enable the Global Interrupts
    //INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();

//    TMR0_SetInterruptHandler(TMR_InterruptHandler);
    LED_ON();
    
    BUZZER_OFF();
    adValue[0] = adValue[1] = adValue[2] = adValue[3] = ADC_GetConversion(channel_FVR);
    FVR_DISABLE();
    ADC_DISABLE();
    
    LED_OFF();
    
    while (1)
    {
        // Add your application code
        SW_ResetPullup();
        SW_SetDigitalOutput();
        SW_SetLow();    // リードスイッチのポートを出力にしてLow出力として省エネ
        WDT_Enable();
        SLEEP();        // ---------------------------------------------------
        //__delay_ms(132);  // デバッガ使用時はディレイに置き換える
        WDT_Disable();
        currentCount.ElapsedTime++;
        FVR_ENABLE();
        ADC_Initialize();
        while(!FVR_ISREADY()){;}
        adValue[adcnt++] = ADC_GetConversion(channel_FVR);
        FVR_DISABLE();
        ADC_DISABLE();
        adcnt &= 0x03;
        
        //LED_SetHigh();
        if( check_vdd( adValue[0] + adValue[1] + adValue[2] + adValue[3] ) )
        {
            soundTable[0].Count = 2;    // 電圧低下、以降は警告のため解放時ブザーを2回にする。
        }
        
        SW_SetPullup();
        SW_SetDigitalInput();    // リードスイッチのポートを入力に戻す
        switch(state)
        {
            case st_Start:
                state = st_Idle;
                break;
            case st_Idle:
                if(ISOPEN())
                {
                    currentNumber = 0;
                    currentCount = initTable;
                    BUZZER_ON();
                    state = st_WarBeep;
                }
                break;
            case st_WarBeep:
                if(ISOPEN())
                {
                    if( ++currentCount.Lenght >= soundTable[currentNumber].Lenght)
                    {
                        BUZZER_OFF();
                        if(++currentCount.Count >= soundTable[currentNumber].Count)
                        {   // 指定回数鳴らしたら。
                            if(++currentNumber >= (sizeof soundTable / sizeof soundTable[0] ) )
                            {   // 想定するパターンの最後まで行っても開きっぱなしの時。
                                currentNumber--;
                                currentCount.ElapsedTime = soundTable[currentNumber -1].ElapsedTime;
                            }
                            state = st_Monitor;
                        }
                        else
                            state = st_WarSilent;
                    }
                }
                else
                {   // Door close
                    BUZZER_OFF();
                    state = st_Idle;
                }
                break;
            case st_WarSilent:
                if(ISOPEN())
                {
                    if( ++currentCount.Lenght >= soundTable[currentNumber].Period)
                    {
                        currentCount.Lenght = 0;
                        BUZZER_ON();
                        state = st_WarBeep;
                    }
                }
                else
                {   // Door close
                    BUZZER_OFF();
                    state = st_Idle;
                }
                break;
            case st_Monitor:
                if(ISOPEN())
                {
                    if( currentCount.ElapsedTime >= soundTable[currentNumber].ElapsedTime)
                    {
                        currentCount.Lenght = 0;
                        currentCount.Count = 0;
                        BUZZER_ON();
                        state = st_WarBeep;
                    }
                }
                else
                {   // Door close
                    BUZZER_OFF();
                    state = st_Idle;
                }
                break;
        }
    }
}
/**
 End of File
*/
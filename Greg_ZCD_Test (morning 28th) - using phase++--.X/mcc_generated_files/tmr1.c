#include <xc.h>
#include "tmr1.h"
volatile uint16_t timer1ReloadVal;
void (*TMR1_InterruptHandler)(void);
void TMR1_Initialize(void)
{
    T1CON = 0x32;
    T1GCON = 0x00;
    T1GATE = 0x00;
    T1CLK = 0x01;
    TMR1H = 0x00;
    TMR1L = 0x00;
    timer1ReloadVal=(TMR1H << 8) | TMR1L;
    PIR4bits.TMR1IF = 0;
    TMR1_StartTimer();
}

void TMR1_StartTimer(void)
{
    T1CONbits.TMR1ON = 1;
}

void TMR1_StopTimer(void)
{
    T1CONbits.TMR1ON = 0;
}

uint16_t TMR1_ReadTimer(void)
{
    uint16_t readVal;
    readVal = (TMR1H << 8) | TMR1L;
    return readVal;
}

void TMR1_WriteTimer(uint16_t timerVal)
{
    if (T1CONbits.nT1SYNC == 1)
    {
        T1CONbits.TMR1ON = 0;
        TMR1H = (timerVal >> 8);
        TMR1L = timerVal;
        T1CONbits.TMR1ON =1;
    }
    else
    {
        TMR1H = (timerVal >> 8);
        TMR1L = timerVal;
    }
}

void TMR1_Reload(void)
{
    TMR1H = (timer1ReloadVal >> 8);
    TMR1L = timer1ReloadVal;
}

void TMR1_StartSinglePulseAcquisition(void)
{
    T1GCONbits.T1GGO = 1;
}

uint8_t TMR1_CheckGateValueStatus(void)
{
    return (T1GCONbits.T1GVAL);
}

bool TMR1_HasOverflowOccured(void)
{
    return(PIR4bits.TMR1IF);
}

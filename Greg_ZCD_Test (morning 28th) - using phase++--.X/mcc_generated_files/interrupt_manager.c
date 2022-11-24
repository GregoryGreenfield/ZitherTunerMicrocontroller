#include "interrupt_manager.h"
#include "mcc.h"


void  INTERRUPT_Initialize (void)
{
    INTCONbits.IPEN = 0;
}
/**
void interrupt INTERRUPT_InterruptManager (void)
{
    // interrupt handler
    if(INTCONbits.PEIE == 1 && PIE2bits.ZCDIE == 1 && PIR2bits.ZCDIF == 1)
    {
        //phase_2();
        // Clear the ZCD interrupt flag
        T1CONbits.TMR1ON = 0; // stop timer
        timer_value = TMR1;
        TMR1_WriteTimer(0x0000);
        TMR1_StartTimer();
        PIR2bits.ZCDIF=0;
        //INTCON=0xE7;
    }
    else
    {
        //Unhandled Interrupt
    }
}*/
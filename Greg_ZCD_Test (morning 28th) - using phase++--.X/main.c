#include "mcc_generated_files/mcc.h"
#include "stdio.h"
int phase=0;
uint16_t timer_value;
int y = 999; // PWM DC at 100%
int n = 0;   // PWM DC at 0%
int delay = 20; // value passed to Delay_tenthSec- can go to speed of delay =2 and __delay_ms(1)
void Delay_tenthSec(unsigned char ds){
    unsigned char i, x;
    for (i=0; i<ds; i++){
        __delay_ms(3);
    }
}

void phase_1(){    
    LATA=0x04;
}
void phase_2(){
    LATA=0x06;
}
void phase_3(){
    LATA=0x02;
}
void phase_4(){
    LATA=0x00;
}
void do_nothing(){
    TRISA=0xFF;
    Delay_tenthSec(delay); 
}

void T_4(){
        Delay_tenthSec(delay);
        phase_1();
        Delay_tenthSec(delay);
        phase_2();
        Delay_tenthSec(delay);
        phase_3();
        Delay_tenthSec(delay);
        phase_4();    
}
void S_4(){
        Delay_tenthSec(delay);
        phase_4();
        Delay_tenthSec(delay);
        phase_3();
        Delay_tenthSec(delay);
        phase_2();
        Delay_tenthSec(delay);
        phase_1(); 
}


void phases(){
    if(phase<1){
        phase=phase+4;
    }
    if(phase>4){
        phase=phase-4;
    }
    if(phase=1){
        phase_1();
        Delay_tenthSec(delay);
    }
    if(phase=2){
        phase_2();
        Delay_tenthSec(delay);
    }
    if(phase=3){
        phase_3();
        Delay_tenthSec(delay);
    }
    if(phase=4){
        phase_4();
        Delay_tenthSec(delay);
    }
    
}

void interrupt INTERRUPT_InterruptManager (void)
{
    // interrupt handler
    if(INTCONbits.PEIE == 1 && PIE2bits.ZCDIE == 1 && PIR2bits.ZCDIF == 1)
    {
        T1CONbits.TMR1ON = 0; // stop timer
        timer_value = TMR1; // update global variable for main program
        TMR1_WriteTimer(0x0000); // reset timer to 0
        TMR1_StartTimer(); // start timer again
        PIR2bits.ZCDIF=0; // 
    }
    else
    {
        //Unhandled Interrupt
    }
}

void  INTERRUPT_Initialize (void)
{
    // Disable Interrupt Priority Vectors (16CXXX Compatibility Mode)
    INTCONbits.IPEN = 0;
}

void main(void){
    INTCON=0xE7;
    SYSTEM_Initialize();    
    PWM1_Initialize();
    ZCD_Initialize();
    TRISA=0x00;
    PWM1_LoadDutyValue(107); // external clock signal for SCF // shld be tmr4 432us, and 107 is 50%
    double need_cnts = 43245; // this is for 46.25Hz. Calculated from string period divided by the timer period.
    double greater = need_cnts*1.015;
    double g_boundary = need_cnts*1.985; // 25Hz
    double fewer = need_cnts*0.9955;
    double f_boundary = need_cnts*0.6; // 77Hz
    
    double over_need_cnts = need_cnts*0.9; // this is for 46.25Hz. Calculated from string period divided by the timer period.
    double over_greater = over_need_cnts*1.015;
    double over_g_boundary = over_need_cnts*1.985*1.2; // 25Hz
    double over_fewer = over_need_cnts*0.9955*0.08;
    double over_f_boundary = over_need_cnts*0.6; // 77Hz
    
    // need_cnts was secondly 43445
    /**
    while(1){
        phase_1();
        phase_2();
        phase_3();
        phase_4();
    }*/
    
    while(1){
        if(timer_value>over_g_boundary){ // section 1
            TRISA=0xFF;
            Delay_tenthSec(delay); 
        }
        if((timer_value<over_g_boundary) && (timer_value>over_greater)){ // section 2
            TRISA=0x00;
            phase++;
            phases();
        }
        if((timer_value<over_greater) && (timer_value>over_fewer)){ // section 3
            while(1){
                if(timer_value>g_boundary){ // section 3.1
                    TRISA=0xFF;
                    Delay_tenthSec(delay); 
                }
                if((timer_value<g_boundary) && (timer_value>greater)){ // section 3.2
                    TRISA=0x00;
                    phase++;
                    phases();
                }
                if((timer_value<greater) && (timer_value>fewer)){ // section 3.3
                    TRISA=0xFF;
                    Delay_tenthSec(delay); 
                }
                if((timer_value<fewer) && (timer_value>f_boundary)){ // section 3.4
                    TRISA=0x00;
                    phase--; 
                    phases();
                }
                if(timer_value<f_boundary){ // section 3.5
                    TRISA=0xFF;
                    Delay_tenthSec(delay); 
                }
            }
        }
        if((timer_value<over_fewer) && (timer_value>over_f_boundary)){ // section 4
            TRISA=0x00;
            phase--; 
            phases();
        }
        if(timer_value<over_f_boundary){ // section 5
            TRISA=0xFF;
            Delay_tenthSec(delay); 
        }
    }
}
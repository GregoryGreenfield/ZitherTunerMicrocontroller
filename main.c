#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/zcd.h"
#include "mcc_generated_files/tmr1.h"
#include "mcc_generated_files/tmr4.h"
#include "mcc_generated_files/pin_manager.h"
#include "mcc_generated_files/interrupt_manager.h"
#include "mcc_generated_files/pwm1.h"
#include "stdio.h"

uint16_t timer_value;

int Current_TMR1_Value(int);
int y = 999; // PWM DC at 100%
int n = 0;   // PWM DC at 0%
int delay = 20; // value passed to Delay_tenthSec- can go to speed of delay =2 and __delay_ms(1)
void Delay_tenthSec(unsigned char ds){
    unsigned char i, x;
    for (i=0; i<ds; i++){
        for(x=0; x<1; x++){
            __delay_ms(1);
        }
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

int phase_number=1;

void phases(void){
    if(phase_number<1){
        phase_number=phase_number+4;
    }
    if(phase_number>4){
        phase_number=phase_number-4;  
    }
    if (phase_number=1){
        phase_1();
        Delay_tenthSec(delay);
    }
    if (phase_number=2){
        phase_2();
        Delay_tenthSec(delay);
    }
    if (phase_number=3){
        phase_3();
        Delay_tenthSec(delay);
    }
    if (phase_number=4){
        phase_4();
        Delay_tenthSec(delay);
    }
    else{
        ;
    }
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
}

void  INTERRUPT_Initialize (void)
{
    // Disable Interrupt Priority Vectors (16CXXX Compatibility Mode)
    INTCONbits.IPEN = 0;
}

void main(void){
    // Initialize the device
    INTCON=0xE7;
    SYSTEM_Initialize();    
    PWM1_Initialize();
    ZCD_Initialize();
    TRISA=0x00;
    
    
    PWM1_LoadDutyValue(107); // external clock signal for SCF // shld be tmr4 432us, and 107 is 50%
    double need_cnts = 43445; // this is for 46.25Hz. Calculated from string period divided by the timer period.
    double greater = need_cnts*1.0015;
    double g_boundary = need_cnts*1.35;
    double fewer = need_cnts*0.9985;
    double f_boundary = need_cnts*0.65;
    
    // need_cnts is theoretically 43245, but experimentally is 43445;
    while (1){
        // TMR1 is the count value the clock has reached since the last sample.        
        if((timer_value>f_boundary && timer_value<g_boundary) || (timer_value<fewer && timer_value>greater)){
            TRISA=0xFF;
            Delay_tenthSec(delay); 
        }
        else{
            if (timer_value>fewer){
                TRISA=0x00;
                T_4();
            }
            if(timer_value<greater){
                TRISA=0x00;
                S_4();
            }
        }
    }
}
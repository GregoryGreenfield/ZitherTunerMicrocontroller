/**
  ZCD Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    zcd.c

  @Summary
    This is the generated driver implementation file for the ZCD driver using MPLAB(c) Code Configurator

  @Description
    This header file provides implementations for driver APIs for ZCD.
    Generation Information :
        Product Revision  :  MPLAB(c) Code Configurator - 4.15
        Device            :  PIC18F46K40
        Driver Version    :  2.00
    The generated drivers are tested against the following:
        Compiler          :  XC8 1.35
        MPLAB             :  MPLAB X 3.40
*/

/*
    (c) 2016 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

/**
  Section: Included Files
*/

#include <xc.h>
#include "zcd.h"

/**
  Section: ZCD Module APIs
*/

void ZCD_Initialize (void)
{
     // Set the ZCD to the options selected in the User Interface
    
    // ZCDPOL not inverted; ZCDSEN enabled; ZCDINTP enabled; ZCDINTN disabled; 
    //ZCDCON = 0x00;
    ZCDCON = 0x82;

    // Clearing IF flag before enabling the interrupt.
    PIR2bits.ZCDIF = 0;
    
    // Enabling ZCD interrupt.
    PIE2bits.ZCDIE = 1;
}

bool ZCD_IsLogicLevel(void)
{
    // Return ZCD logic level depending on the output polarity selected.
    return (ZCDCONbits.ZCDOUT);
}

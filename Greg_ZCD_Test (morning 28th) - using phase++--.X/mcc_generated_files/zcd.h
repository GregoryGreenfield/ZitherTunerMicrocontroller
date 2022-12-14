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

#ifndef _ZCD_H
#define _ZCD_H

/**
  Section: Included Files
*/

#include <xc.h>
#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif

/**
  Section: ZCD Module APIs
*/

/**
  @Summary
    Initializes the ZCD_Initialize.

  @Description
    This routine initializes the ZCD_Initialize.
    This routine must be called before any other ZCD routine is called.
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
    ZCD_Initialize();
    </code>
 */
void ZCD_Initialize(void);

/**
  @Summary
    Determines if current is sinking or sourcing

  @Description
    This routine is used to determine if current is sinking or sourcing
    depending on output polarity.

    For non inverted polarity:
    high - Indicates current is sinking
    low - Indicates current is sourcing

    For inverted polarity:
    high - Indicates current is sourcing
    low - Indicates current is sinking

  @Preconditions
    ZCD_Initialize() function should have been called before calling this function.

  @Param
    None

  @Returns
   high or low

  @Example
    <code>
    ZCD_Initialize();

    if(ZCD_IsLogicLevel())
    {
        // User code..
    }
    else
    {
        // User code..
    }
    </code>
 */
bool ZCD_IsLogicLevel(void);

/**
  @Summary
    Implements ISR.

  @Description
    This routine is used to implement the ISR for the interrupt-driven
    implementations.

  @Returns
    None

  @Param
    None
*/
void ZCD_ISR(void);

#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif

#endif  //_ZCD_H
/**
 End of File
*/


#include <xc.h>
#include "zcd.h"

void ZCD_Initialize (void)
{
    ZCDCON = 0x82;
    PIR2bits.ZCDIF = 0;
    PIE2bits.ZCDIE = 1;
}
bool ZCD_IsLogicLevel(void)
{
    return (ZCDCONbits.ZCDOUT);
}

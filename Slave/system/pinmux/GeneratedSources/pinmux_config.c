/*
 **
 ** Source file generated on April 21, 2021 at 17:16:24.	
 **
 ** Copyright (C) 2011-2021 Analog Devices Inc., All Rights Reserved.
 **
 ** This file is generated automatically based upon the options selected in 
 ** the Pin Multiplexing configuration editor. Changes to the Pin Multiplexing
 ** configuration should be made by changing the appropriate options rather
 ** than editing this file.
 **
 ** Selected Peripherals
 ** --------------------
 ** SPI (SCK, MISO, MOSI, SS)
 **
 ** GPIO (unavailable)
 ** ------------------
 ** PF11, PF12, PF13, PF14
 */

#include <sys/platform.h>
#include <stdint.h>

#define SPI_SCK_PORTF_FER  ((uint16_t) ((uint16_t) 1<<13))
#define SPI_MISO_PORTF_FER  ((uint16_t) ((uint16_t) 1<<12))
#define SPI_MOSI_PORTF_FER  ((uint16_t) ((uint16_t) 1<<11))
#define SPI_SS_PORTF_FER  ((uint16_t) ((uint16_t) 1<<14))

int32_t adi_initpinmux(void);

/*
 * Initialize the Port Control MUX and FER Registers
 */
int32_t adi_initpinmux(void) {

    /* PORTx_FER registers */
    *pPORTF_FER = SPI_SCK_PORTF_FER | SPI_MISO_PORTF_FER
     | SPI_MOSI_PORTF_FER | SPI_SS_PORTF_FER;
    return 0;
}


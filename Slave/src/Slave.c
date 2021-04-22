/*****************************************************************************
 * Slave.c
 *****************************************************************************/

#include <sys/platform.h>
#include <defBF537.h>
#include <cdefBF537.h>
#include <ccblkfn.h>
#include "adi_initialize.h"
#include "Slave.h"

/** 
 * If you want to use command program arguments, then place them in the following string. 
 */
char __argv_string[] = "";

void spiInitialization()
{
	uint16_t controlRegister = SPI_CTL;

	// Enable PF11(MOSI) & PF13(SCK) as input
	*pPORTFIO_INEN = (1<<11) | (1<<13);


	//initialize device as slave device,
	//by activating bit 12 of the
	//SPI_CTL Register
	controlRegister |= 0x1000;
}


int main(int argc, char *argv[])
{
	/**
	 * Initialize managed drivers and/or services that have been added to 
	 * the project.
	 * @return zero on success 
	 */
	adi_initComponents();
	spiInitialization();


	return 0;
}

